/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_22_heredoc_sig.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:04:30 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/08 21:11:15 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_heredoc_if_sigint(t_tr *t)
{
	if (t->exit_status != 130)
		return ;
	ft_heredoc_file("close", t);
	ft_unlink_heredoc(t);
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
	ft_free_str(&t->f_line);
	ft_free_str(&t->f_path);
	ft_free_int(&t->f_pids);
	ft_free_2d_int(&t->f_pipes);
	t->tkn_heredoc_tracer = NULL;
}

static void	ft_readfile(char *lim, char **f_str, char **f_file, t_tr *t)
{
	ft_signal_handler_sigint_dflt(t);
	*f_str = readline(t->hd_prompt);
	while (*f_str && ft_strncmp(*f_str, lim, ft_strlen(lim) + 1))
	{
		ft_add_str_malloc(f_file, *f_str, ft_strlen(*f_str) + 1, t);
		ft_strlcpy(*f_file + ft_strlen(*f_file), "\n", 2);
		ft_free_str(f_str);
		*f_str = readline(t->hd_prompt);
	}
	ft_signal_all_ignore(t);
}

static void	ft_readfile_and_exit_child(char *lim, t_tr *t)
{
	char		*f_str;
	char		*f_file;

	ft_reset_std(t);
	ft_close_catched_stds(t);
	f_file = NULL;
	f_str = NULL;
	ft_readfile(lim, &f_str, &f_file, t);
	if (!f_str)
	{
		t->err = t->err_list->heredoc_eof;
		ft_w(!f_str, NULL, t);
	}
	if (f_file)
	{
		ft_heredoc_file("open", t);
		write(t->hd_fd, f_file, ft_strlen(f_file));
	}
	ft_heredoc_file("close", t);
	ft_free_str(&f_str);
	ft_free_str(&f_file);
	t->exit_status = 0;
	t->do_exit = 1;
	ft_free_all(t);
}

void	ft_heredoc_fork_readfile(char *lim, t_tr *t)
{
	char					*f_str;
	int						pid;
	int						wsts;

	pid = fork();
	ft_err(pid < 0, t, __FILE__, __LINE__);
	if (!pid)
		ft_readfile_and_exit_child(lim, t);
	ft_err(wait(&wsts) < 0, t, __FILE__, __LINE__);
	f_str = NULL;
	if (WIFSIGNALED(wsts))
	{
		write(1, "\n", 1);
		t->exit_status = WTERMSIG(wsts) + 128;
		f_str = ft_itoa(t->exit_status);
		ft_strlcpy(t->exit_les, f_str, ft_strlen(f_str) + 1);
		ft_free_str(&f_str);
	}
}

void	ft_heredoc_file(char *mode, t_tr *t)
{
	char					*hstr;
	char					*f_num;
	int						k;

	if (*mode == 'n')
	{
		hstr = t->hd_filename + ft_strlen(t->hd_filemask);
		k = ft_atoi(hstr) + 1;
		f_num = ft_itoa(k);
		ft_strlcpy(hstr, f_num, ft_strlen(f_num) + 1);
		ft_free_str(&f_num);
		t->hd_fd = open(t->hd_filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_free_close_fd(&t->hd_fd, t);
	}
	else if (*mode == 'o')
	{
		ft_err(t->hd_fd >= 0, t, __FILE__, __LINE__);
		t->hd_fd = open(t->hd_filename, O_RDWR | O_TRUNC, 0777);
		ft_err(t->hd_fd < 0, t, __FILE__, __LINE__);
	}
	else if (*mode == 'c')
		ft_free_close_fd(&t->hd_fd, t);
	ft_err(*mode != 'n' && *mode != 'o' && *mode != 'c', t, __FILE__, __LINE__);
}
