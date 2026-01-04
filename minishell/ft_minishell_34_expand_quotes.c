/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_34_expand_quotes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:23:39 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 14:34:20 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_expand_quotes_parse(char *exp, char **f_s, t_tr *t)
{
	int		i;

	if (!exp || !*exp)
		return (0);
	i = 0;
	while (t->qs_on && exp[i] && exp[i] != '\'')
		i++;
	while (t->qd_on && exp[i] && exp[i] != '\"')
		i++;
	while (exp[i] && exp[i] != '\"' && exp[i] != '\'')
		i++;
	ft_add_str_malloc(f_s, exp, i, t);
	return (i);
}

void	ft_expand_quotes(int encl, t_tkn *tkn, t_tr *t)
{
	char	*f_exp;
	char	*exp;

	if (!t->tkn_head || !tkn)
		return ;
	f_exp = NULL;
	while (tkn && !((tkn->brace_close || tkn->ao_and \
		|| tkn->ao_or) && tkn->enclsr == encl))
	{
		if (tkn->word && (tkn->exp_qd || tkn->exp_qs) && tkn->enclsr == encl)
		{
			ft_add_str_malloc(&f_exp, tkn->f_str, ft_strlen(tkn->f_str), t);
			exp = f_exp;
			ft_reset_qds(t);
			ft_free_str(&tkn->f_str);
			while (*exp)
			{
				exp += ft_quotes_status(exp, t);
				exp += ft_expand_quotes_parse(exp, &tkn->f_str, t);
			}
			ft_free_str(&f_exp);
		}
		tkn = tkn->next;
	}
}
