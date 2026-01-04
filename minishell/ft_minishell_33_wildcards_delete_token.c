/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_33_wildcards_delete_token.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:18:44 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 14:09:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_expand_wildcards_process_tkn(t_tkn **tkn, t_tr *t)
{
	t_tkn	*nxt;
	t_tkn	*prv;

	if ((*tkn)->f_str)
	{
		*tkn = (*tkn)->next;
		return ;
	}
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
