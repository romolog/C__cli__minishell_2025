/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_25_expand_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:23:39 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 21:27:39 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_variable(char *s, char **f_s, t_tr *t)
{
	char	*f_envname;
	char	*f_var;
	int		i;

	f_envname = NULL;
	f_var = NULL;
	i = 1;
	while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') \
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
		i++;
	ft_add_str_malloc(&f_envname, s + 1, i - 1, t);
	ft_getenv(&f_var, f_envname, t);
	if (f_var && *f_var)
		ft_add_str_malloc(f_s, f_var, ft_strlen(f_var), t);
	ft_free_str(&f_envname);
	ft_free_str(&f_var);
	return (i);
}

static int	ft_expand_var_expand(char *s, char **f_s, t_tr *t)
{
	int		i;

	if (t->qs_on || !s || *s != '$')
		return (0);
	i = 1;
	if ((s[i] >= 'a' && s[i] <= 'z') \
		|| (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
		i = ft_variable(s, f_s, t);
	else if (s[i] == '?')
		ft_add_str_malloc(f_s, t->exit_les, ft_strlen(t->exit_les), t);
	return (i + (s[i] == '?'));
}

static void	ft_expand_one_word(t_tkn *tkn, t_tr *t)
{
	char	*f_s;
	char	*exp;

	f_s = NULL;
	exp = tkn->f_str;
	ft_reset_qds(t);
	while (*exp)
	{
		exp += ft_expand_var_quotes(exp, &f_s, t);
		exp += ft_expand_var_passby(exp, &f_s, t);
		exp += ft_expand_var_expand(exp, &f_s, t);
	}
	ft_free_str(&tkn->f_str);
	tkn->f_str = f_s;
	f_s = NULL;
	ft_expand_if_wildcards(tkn, t);
}

static void	ft_expand_var_tokens(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;

	tkn = *ptr_tkn;
	while (t->tkn_head && tkn && !((tkn->brace_close || tkn->ao_and \
		|| tkn->ao_or) && tkn->enclsr == encl))
	{
		if (tkn->word && (tkn->exp_env || tkn->exp_les) && tkn->enclsr == encl)
			ft_expand_one_word(tkn, t);
		if (tkn && !tkn->f_str)
		{
			if ((*ptr_tkn) - tkn == 0)
			{
				ft_expand_delete_null(&tkn, t);
				*ptr_tkn = tkn;
			}
			else
				ft_expand_delete_null(&tkn, t);
		}
		else if (t->tkn_head && tkn)
			tkn = tkn->next;
	}
}

void	ft_expand_var(int encl, t_tkn **tkn, t_tr *t)
{
	ft_expand_var_heredoc(encl, *tkn, t);
	ft_expand_var_tokens(encl, tkn, t);
}
