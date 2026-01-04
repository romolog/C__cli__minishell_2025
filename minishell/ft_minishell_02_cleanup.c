/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_02_cleanup.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:37:49 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/06 16:41:55 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_free_redir_fd(t_tr *t)
{
	int		i;

	i = -1;
	while (++i <= 100)
	{
		if (t->f_redir_fds[i] != -1)
		{
			ft_ctx(close(t->f_redir_fds[i]) < 0, t, __FILE__, __LINE__);
			t->f_redir_fds[i] = -1;
		}
	}
}

void	ft_free_tokens(t_tr *t)
{
	if (!t || !t->tkn_head)
		return ;
	t->tkn_tracer = NULL;
	t->tkn_heredoc_tracer = NULL;
	while (t->tkn_head)
	{
		if (t->tkn_head->next)
		{
			t->tkn_head = t->tkn_head->next;
			ft_free_str(&t->tkn_head->prev->f_str);
			free(t->tkn_head->prev);
		}
		else
		{
			ft_free_str(&t->tkn_head->f_str);
			free(t->tkn_head);
			t->tkn_head = NULL;
		}
	}
}

void	ft_free_pipes(t_tr *t)
{
	int		i;

	if (!t->f_pipes)
		return ;
	i = -1;
	while (++i < t->pipes_num)
	{
		if (t->f_pipes[i])
			free(t->f_pipes[i]);
		t->f_pipes[i] = NULL;
	}
	free(t->f_pipes);
	t->f_pipes = NULL;
	t->pipes_num = 0;
}

void	ft_free_nonexit(t_tr *t)
{
	ft_free_pipes(t);
	ft_free_tokens(t);
	ft_free_str(&t->f_chdir);
	ft_free_str(&t->f_cmd);
	if (t->f_cmd_args)
	{
		free(t->f_cmd_args);
		t->f_cmd_args = NULL;
	}
	ft_free_str(&t->f_cmd_path);
	ft_free_str(&t->f_cwd);
	ft_free_str(&t->f_cwd_prev);
	ft_free_str(&t->f_home);
	ft_free_str(&t->f_line);
	ft_free_redir_fd(t);
	ft_free_str(&t->f_path);
	ft_free_int(&t->f_pids);
	ft_free_pipes(t);
	ft_free_str(&t->f_wldcrd_mask);
}

void	ft_free_all(t_tr *t)
{
	if (!t)
		exit(EXIT_FAILURE);
	ft_free_nonexit(t);
	if (t->do_exit)
	{
		ft_free_str(&t->f_host);
		ft_free_2d_char(&t->f_env);
		ft_free_str(&t->f_path_start);
		ft_free_str(&t->f_prog);
		ft_free_str(&t->f_prompt);
		if (t->redir_fd_stdin >= 0)
			close(t->redir_fd_stdin);
		if (t->redir_fd_stderr >= 0)
			close(t->redir_fd_stderr);
		if (t->redir_fd_stdout >= 0)
			close(t->redir_fd_stdout);
		ft_free_str(&t->f_user);
		exit(t->exit_status);
	}
}
