/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_26_expand_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:23:39 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:21:36 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_expand_var_quotes(char *exp, char **f_s, t_tr *t)
{
	int	done;

	if (!exp || !*exp)
		return (0);
	done = 0;
	done += ((*exp == '\'' || *exp == '\"') && !t->qd_on && !t->qs_on);
	t->qd_on += (*exp == '\"' && !t->qd_on && !t->qs_on);
	t->qs_on += (*exp == '\'' && !t->qd_on && !t->qs_on);
	done -= (!done \
		&& ((*exp == '\"' && t->qd_on) || (*exp == '\'' && t->qs_on)));
	t->qd_on -= (done == -1 && *exp == '\"' && t->qd_on);
	t->qs_on -= (done == -1 && *exp == '\'' && t->qs_on);
	if (done)
		ft_add_str_malloc(f_s, exp, 1, t);
	return (done != 0);
}

int	ft_expand_var_passby(char *exp, char **f_s, t_tr *t)
{
	int	i;

	if (!exp || !*exp)
		return (0);
	i = 0;
	if (t->qs_on)
	{
		while (t->qs_on && exp[i] && exp[i] != '\'')
			i++;
		ft_add_str_malloc(f_s, exp, i, t);
		return (i);
	}
	while (exp[i] && exp[i] != '\"' && \
		(exp[i] != '\'' || t->qd_on) && \
		(exp[i] != '$' || \
		((exp[i + 1] < 'a' || exp[i + 1] > 'z') && \
		(exp[i + 1] < 'A' || exp[i + 1] > 'Z') && \
		exp[i + 1] != '_' && exp[i + 1] != '?')))
		i++;
	if (i)
		ft_add_str_malloc(f_s, exp, i, t);
	return (i);
}

void	ft_expand_if_wildcards(t_tkn *tkn, t_tr *t)
{
	char	*ptr;

	if (!tkn || !tkn->f_str || !*tkn->f_str)
		return ;
	ptr = tkn->f_str;
	while (*ptr && !tkn->exp_wldcrd)
	{
		ft_reset_qds(t);
		ptr += ft_quotes_status(ptr, t);
		while (*ptr && (t->qd_on || t->qs_on) && *ptr != '\"' && *ptr != '\'')
			ptr++;
		while (*ptr && !tkn->exp_wldcrd \
			&& !t->qd_on && !t->qs_on && *ptr != '\"' && *ptr != '\'')
		{
			tkn->exp_wldcrd += *ptr == '*';
			ptr++;
		}
	}
}
