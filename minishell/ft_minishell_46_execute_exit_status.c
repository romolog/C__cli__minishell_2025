/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_46_execute_exit_status.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:42:33 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:50:13 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// could be SIGNAL = 13 (SIGPIPE : Terminate   Write to pipe with no readers)
static void	ft_newline_ifsignalled(int *new_line, int wait_status)
{
	if (!*new_line && WIFSIGNALED(wait_status) \
		&& (WTERMSIG(wait_status) == SIGINT || \
			WTERMSIG(wait_status) == SIGQUIT))
	{
		write(1, "\n", 1);
		*new_line = 1;
	}
}

void	ft_execute_pipe_catch_exit_status(int num_executed, t_tr *t)
{
	int			i;
	int			k;
	int			wait_status;
	char		*f_str;
	int			new_line;

	new_line = 0;
	i = -1;
	while (++i < num_executed)
	{
		k = waitpid(t->f_pids[i], &wait_status, 0);
		ft_err(k == -1, t, __FILE__, __LINE__);
		ft_newline_ifsignalled(&new_line, wait_status);
		if (k == t->f_pids[t->cmd_num - 1])
		{
			t->exit_status = 255;
			if (WIFEXITED(wait_status))
				t->exit_status = WEXITSTATUS(wait_status);
			else if (WIFSIGNALED(wait_status))
				t->exit_status = WTERMSIG(wait_status) + 128;
			f_str = ft_itoa(t->exit_status);
			ft_strlcpy(t->exit_les, f_str, ft_strlen(f_str) + 1);
			ft_free_str(&f_str);
		}
	}
}
