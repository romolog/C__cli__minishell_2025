/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_36_redir_stdin_stdout.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:50:38 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/11 16:42:44 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_do_redirection_file_in(int *fd, t_tkn *tkn, t_tr *t)
{
	if (access(tkn->f_str, F_OK))
		t->err = t->err_list->no_file;
	else if (access(tkn->f_str, R_OK))
		t->err = t->err_list->perm_denied;
	if (access(tkn->f_str, F_OK) || access(tkn->f_str, R_OK))
	{
		ft_e(1, tkn->f_str, NULL, t);
		return (1);
	}
	*fd = open(tkn->f_str, O_RDONLY);
	ft_err(*fd < 0, t, __FILE__, __LINE__);
	return (0);
}

static int	ft_do_redirection_file_out(int *fd, t_tkn *tkn, t_tr *t)
{
	if (ft_is_directory(tkn->f_str, t) == 1)
	{
		t->err = t->err_list->is_dir;
		ft_e(1, tkn->f_str, NULL, t);
		return (1);
	}
	if (!ft_is_valid_redir_directory(tkn, t))
		return (1);
	if (!ft_is_valid_file_path(tkn, t))
		return (1);
	if (tkn->prev->redir_output_trunc)
		*fd = open(tkn->f_str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (tkn->prev->redir_output_append)
		*fd = open(tkn->f_str, O_RDWR | O_CREAT | O_APPEND, 0777);
	ft_err(*fd < 0, t, __FILE__, __LINE__);
	return (0);
}

static void	ft_redirection_fd(int *err, int *fdr, t_tkn *tkn, t_tr *t)
{
	int		i;

	if (*err || !tkn->prev->prev || !tkn->prev->prev->w_redir_fd)
		return ;
	*fdr = ft_atoi_fd(tkn->prev->prev->f_str, t);
	*err += (*fdr == -1);
	if (*err)
		return ;
	i = 0;
	while (t->f_redir_fds[i] != -1 && i < 100 && t->f_redir_fds[i] != *fdr)
		i++;
	if (i == 100)
	{
		t->err = t->err_list->fd_num_exceeded;
		ft_e(1, tkn->prev->f_str, tkn->prev->prev->f_str, t);
		*err = 1;
		return ;
	}
	else if (t->f_redir_fds[i] == *fdr)
		ft_err(close(*fdr) == -1, t, __FILE__, __LINE__);
	t->f_redir_fds[i] = *fdr;
}

int	ft_redir_file(int fd_redir, t_tkn *tkn, t_tr *t)
{
	int		err;
	int		fd;

	err = 0;
	fd = -1;
	if (fd_redir == STDIN_FILENO && tkn->redir_file_heredoc)
	{
		fd = open(tkn->f_str, O_RDWR);
		ft_err(fd < 0, t, __FILE__, __LINE__);
	}
	else if (fd_redir == STDIN_FILENO && !tkn->redir_file_heredoc)
		err = ft_do_redirection_file_in(&fd, tkn, t);
	else if (fd_redir == STDOUT_FILENO)
		err = ft_do_redirection_file_out(&fd, tkn, t);
	ft_redirection_fd(&err, &fd_redir, tkn, t);
	if (!err)
	{
		ft_err(dup2(fd, fd_redir) == -1, t, __FILE__, __LINE__);
		ft_err(close(fd) == -1, t, __FILE__, __LINE__);
	}
	ft_redir_delete_tkns(tkn->prev, t);
	return (err);
}
