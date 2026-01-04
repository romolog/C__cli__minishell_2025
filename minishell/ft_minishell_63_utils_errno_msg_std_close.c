/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_63_utils_errno_msg_std_close.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:11:49 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/07 16:49:58 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_set_errno_messages(int errnum, t_tr *t)
{
	if (errnum == EACCES)
		t->err = t->err_list->perm_denied;
	else if (errnum == ENOENT)
		t->err = t->err_list->no_file;
	else if (errnum == ENOTDIR)
		t->err = t->err_list->not_dir;
}

void	ft_close_catched_stds(t_tr *t)
{
	ft_free_close_fd(&t->redir_fd_stdin, t);
	ft_free_close_fd(&t->redir_fd_stderr, t);
	ft_free_close_fd(&t->redir_fd_stdout, t);
}
