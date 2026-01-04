/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_06_tracker.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:35:27 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/06 16:13:39 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_set_f_before_all(t_tr *t)
{
	t->f_chdir = NULL;
	t->f_cmd = NULL;
	t->f_cmd_args = NULL;
	t->f_cmd_path = NULL;
	t->f_cwd = NULL;
	t->f_cwd_prev = NULL;
	t->f_env = NULL;
	t->f_home = NULL;
	t->f_host = NULL;
	t->f_line = NULL;
	t->f_path = NULL;
	t->f_path_start = NULL;
	t->f_pids = NULL;
	t->f_pipes = NULL;
	t->f_prog = NULL;
	t->f_prompt = NULL;
	t->tkn_head = NULL;
	t->f_user = NULL;
	t->f_wldcrd_mask = NULL;
	t->tkn_tracer = NULL;
	t->tkn_heredoc_tracer = NULL;
}

static void	ft_set_quote_vars(t_tr *t)
{
	t->qb = 0;
	t->qb_on = 0;
	t->qd = 0;
	t->qd_on = 0;
	t->qs = 0;
	t->qs_on = 0;
}

static void	ft_set_env(char *envp[], t_tr *t)
{
	int		i;
	int		errnum;

	i = 0;
	while (envp[i])
		i++;
	t->f_env = malloc(sizeof(char *) * (i + 1));
	ft_err(!t->f_env, t, __FILE__, __LINE__);
	t->f_env[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		t->f_env[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!t->f_env[i])
		{
			errnum = errno;
			while (--i >= 0)
				ft_free_str(t->f_env + i);
			free(t->f_env);
			t->f_env = NULL;
			errno = errnum;
			ft_err(1, t, __FILE__, __LINE__);
		}
		ft_strlcpy(t->f_env[i], envp[i], ft_strlen(envp[i]) + 1);
	}
}

static void	ft_set_heredoc_redir(t_tr *t)
{
	int		i;
	char	*mask;
	char	*tty_heredoc;

	mask = "a_minishell_heredoc_";
	tty_heredoc = "\033[0;36mhere_doc> \033[0m";
	ft_strlcpy(t->hd_filemask, mask, \
				ft_strlen(mask) + 1);
	ft_strlcpy(t->hd_filename, t->hd_filemask, \
				ft_strlen(t->hd_filemask) + 1);
	ft_strlcpy(t->hd_filename + ft_strlen(t->hd_filemask), "0", 2);
	ft_strlcpy(t->hd_filename_0, t->hd_filename, \
				ft_strlen(t->hd_filename) + 1);
	ft_strlcpy(t->hd_prompt, tty_heredoc, \
				ft_strlen(tty_heredoc) + 1);
	i = -1;
	while (++i < 101)
		t->f_redir_fds[i] = -1;
	t->hd_fd = -1;
}

void	ft_set_tracker(int argc, char *argv[], char *envp[], t_tr *t)
{
	ft_set_f_before_all(t);
	ft_set_tracker_catch_std(t);
	ft_set_tracker_prog_name(argv[0], t);
	t->ac = argc;
	ft_check_argc(t);
	t->pid_current = 1;
	ft_set_quote_vars(t);
	t->av = argv;
	ft_set_env(envp, t);
	ft_set_tracker_shell_level(t);
	ft_set_heredoc_redir(t);
	t->do_exit = 0;
	ft_strlcpy(t->exit_les, "0", 2);
	t->exit_status = EXIT_SUCCESS;
	t->cmd_num = 0;
	t->pipes_num = 0;
	t->token_max_enclsr = 0;
	t->token_qty = 0;
	ft_set_tracker_start_path(t);
	ft_set_tracker_prompt(t);
}
