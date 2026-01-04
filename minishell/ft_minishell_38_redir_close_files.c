/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_38_redir_close_files.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:15:54 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/06 13:38:54 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_redir_close_files(t_tr *t)
{
	int	i;

	if (t->f_redir_fds[0] == -1)
		return ;
	i = -1;
	while (t->f_redir_fds[++i] != -1)
	{
		ft_err(close(t->f_redir_fds[i]) == -1, t, __FILE__, __LINE__);
		t->f_redir_fds[i] = -1;
	}
}
