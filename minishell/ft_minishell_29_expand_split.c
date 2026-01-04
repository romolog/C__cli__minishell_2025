/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_29_expand_split.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:38:51 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/10 21:09:20 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_if_expand_wildcards(char *str, t_tr *t)
{
	if (!str || !*str)
		return (0);
	ft_reset_qds(t);
	while (*str)
	{
		str += ft_quotes_status(str, t);
		while (*str && t->qd_on && *str != '\"')
			str++;
		while (*str && t->qs_on && *str != '\'')
			str++;
		while (*str && *str != '\"' && *str != '\'' && *str != '*' )
			str++;
		if (*str == '*' && !t->qd_on && !t->qs_on)
			return (1);
	}
	return (0);
}

static void	ft_expand_split_add_token(char *exp, char **f_s, int encl, t_tr *t)
{
	t_tkn	*tkn;
	t_tkn	*temp;

	tkn = t->tkn_tracer;
	temp = ft_calloc(1, sizeof(t_tkn));
	ft_err(!temp, t, __FILE__, __LINE__);
	temp->word = 1;
	temp->f_str = NULL;
	if (exp)
		ft_add_str_malloc(&temp->f_str, exp, ft_strlen(exp), t);
	temp->enclsr = encl;
	temp->exp_qd = ft_strchr(exp, '\"') || ft_strchr(exp, '\'');
	temp->exp_wldcrd = ft_if_expand_wildcards(exp, t);
	if (tkn->next)
		tkn->next->prev = temp;
	temp->next = tkn->next;
	tkn->next = temp;
	temp->prev = tkn;
	ft_free_str(&tkn->f_str);
	tkn->f_str = *f_s;
	*f_s = NULL;
	ft_reset_qds(t);
	t->tkn_tracer = temp;
}

int	ft_expand_split_tokens(char *exp, char **f_s, int encl, t_tr *t)
{
	int		i;

	if (!exp || t->qd_on || t->qs_on \
		|| (*exp != ' ' && *exp != '\t' && *exp != '\n'))
		return (0);
	i = 0;
	while (exp[i] && (exp[i] == ' ' || exp[i] == '\t' || exp[i] == '\n'))
		i++;
	if (*f_s && **f_s && exp[i])
		ft_expand_split_add_token(exp + i, f_s, encl, t);
	else if (*f_s && **f_s && !exp[i])
	{
		ft_free_str(&t->tkn_tracer->f_str);
		t->tkn_tracer->f_str = *f_s;
		*f_s = NULL;
	}
	else if ((!*f_s || !**f_s) && !exp[i])
		ft_free_str(&t->tkn_tracer->f_str);
	else if ((!*f_s || !**f_s) && exp[i])
	{
		ft_free_str(&t->tkn_tracer->f_str);
		ft_add_str_malloc(&t->tkn_tracer->f_str, \
					exp + i, ft_strlen(exp + i), t);
	}
	return (i);
}

int	ft_is_split(int encl, t_tkn *tkn, char *str, t_tr *t)
{
	if (!tkn || !tkn->word || tkn->enclsr != encl)
		return (0);
	if (!str)
		return (0);
	if (!*str)
		return (1);
	ft_reset_qds(t);
	while (*str)
	{
		str += ft_quotes_status(str, t);
		while (t->qd_on && *str && *str != '\"')
			str++;
		while (t->qs_on && *str && *str != '\'')
			str++;
		while (*str && *str != '\"' && *str != '\'' \
			&& *str != ' ' && *str != '\t' && *str != '\n')
			str++;
		if (!t->qd_on && !t->qs_on && \
			(*str == ' ' || *str == '\t' || *str == '\n'))
			return (1);
	}
	return (0);
}
