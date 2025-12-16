/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_28_expand_split.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:40 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/10 21:09:39 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_expand_split_quotes(char *exp, char **f_s, t_tr *t)
{
	if (*exp != '\"' && *exp != '\'')
		return (0);
	if (ft_quotes_status(exp, t))
	{
		ft_add_str_malloc(f_s, exp, 1, t);
		return (1);
	}
	return (0);
}

static int	ft_expand_split_passby(char *exp, char **f_s, t_tr *t)
{
	int	i;

	if (!exp || !*exp)
		return (0);
	i = 0;
	while (t->qd_on && exp[i] && exp[i] != '\"')
		i++;
	while (t->qs_on && exp[i] && exp[i] != '\'')
		i++;
	while (!t->qd_on && !t->qs_on && exp[i] \
		&& exp[i] != ' ' && exp[i] != '\t' && exp[i] != '\n' \
		&& exp[i] != '\"' && exp[i] != '\'')
		i++;
	ft_add_str_malloc(f_s, exp, i, t);
	return (i);
}

static void	ft_call_expand_split(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;
	char	*f_s;
	char	*f_exp;
	char	*exp;

	tkn = *ptr_tkn;
	f_exp = NULL;
	ft_add_str_malloc(&f_exp, tkn->f_str, ft_strlen(tkn->f_str), t);
	exp = f_exp;
	ft_reset_qds(t);
	f_s = NULL;
	if (tkn && *exp)
	{
		while (*exp && *exp != ' ' && *exp != '\t' && *exp != '\n')
		{
			exp += ft_expand_split_quotes(exp, &f_s, t);
			exp += ft_expand_split_passby(exp, &f_s, t);
		}
		t->tkn_tracer = tkn;
		exp += ft_expand_split_tokens(exp, &f_s, encl, t);
		tkn = t->tkn_tracer;
	}
	ft_free_str(&f_exp);
	ft_free_str(&f_s);
	*ptr_tkn = tkn;
}

void	ft_expand_delete_null(t_tkn **tkn, t_tr *t)
{
	t_tkn	*prv;
	t_tkn	*nxt;

	if (*tkn && (*tkn)->f_str)
		return ;
	prv = (*tkn)->prev;
	nxt = (*tkn)->next;
	free(*tkn);
	*tkn = nxt;
	if (!prv && !nxt)
	{
		ft_strlcpy(t->exit_les, "0", 2);
		t->exit_status = 0;
		t->tkn_head = NULL;
	}
	if (!prv)
		t->tkn_head = nxt;
	if (prv)
		prv->next = nxt;
	if (nxt)
		nxt->prev = prv;
}

void	ft_expand_split(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;

	tkn = *ptr_tkn;
	while (t->tkn_head && tkn && !((tkn->brace_close || tkn->ao_and \
		|| tkn->ao_or) && tkn->enclsr == encl))
	{
		if (tkn->word && tkn->enclsr == encl && !tkn->f_str)
		{
			if (*ptr_tkn - tkn == 0)
			{
				ft_expand_delete_null(&tkn, t);
				*ptr_tkn = tkn;
			}
			else
				ft_expand_delete_null(&tkn, t);
		}
		else if (ft_is_split(encl, tkn, tkn->f_str, t))
			ft_call_expand_split(encl, &tkn, t);
		else if (t->tkn_head && tkn)
			tkn = tkn->next;
	}
}
