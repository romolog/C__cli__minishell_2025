/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_15_invalid_line.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:51:41 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/08 18:23:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_reset_qds(t_tr *t)
{
	t->qb = 0;
	t->qb_on = 0;
	t->qd = 0;
	t->qd_on = 0;
	t->qs = 0;
	t->qs_on = 0;
}

static void	ft_process_error(int i, int *res, t_tr *t)
{
	t->err = t->err_list->overflow;
	ft_e(t->f_line && t->f_line[i], NULL, NULL, t);
	*res += (t->f_line && t->f_line[i]);
	t->err = (t->err_list)->unmatched_quote;
	ft_e((t->qb % 2 || t->qd % 2 || t->qs % 2), NULL, NULL, t);
	*res += (t->qb % 2 || t->qd % 2 || t->qs % 2);
	if (!*res)
		return ;
	t->exit_status = 1;
	ft_strlcpy(t->exit_les, "1", 2);
}

static int	ft_unmatch_quote(t_tr *t)
{
	size_t	i;
	int		res;

	ft_reset_qds(t);
	res = (!t->f_line || !*t->f_line);
	i = 0;
	while (!res && t->f_line[i] && i < __UINT32_MAX__)
	{
		t->qb += (t->f_line[i] == '`') * (!t->qd_on && !t->qs_on);
		t->qb_on += (!t->qb_on && !t->qd_on && !t->qs_on && t->qb % 2) \
			- (t->qb_on && !(t->qb % 2));
		t->qd += (t->f_line[i] == '\"') * (!t->qb_on && !t->qs_on);
		t->qd_on += (!t->qb_on && !t->qd_on && !t->qs_on && t->qd % 2) \
			- (t->qd_on && !(t->qd % 2));
		t->qs += (t->f_line[i] == '\'') * (!t->qb_on && !t->qd_on);
		t->qs_on += (!t->qb_on && !t->qd_on && !t->qs_on && t->qs % 2) \
			- (t->qs_on && !(t->qs % 2));
		i++;
	}
	ft_process_error(i, &res, t);
	ft_reset_qds(t);
	return (res);
}

// keep previous exit status if no tokens
static int	ft_no_tokens(t_tr *t)
{
	int		i;

	i = 0;
	while (t->f_line && (t->f_line[i] == ' ' || t->f_line[i] == '\t'))
		i++;
	if (!t->f_line || !t->f_line[i])
		return (1);
	return (0);
}

int	ft_invalid_line(t_tr *t)
{
	if (ft_no_tokens(t) || ft_unmatch_quote(t))
	{
		ft_free_str(&t->f_line);
		ft_free_tokens(t);
		return (1);
	}
	add_history(t->f_line);
	return (0);
}
