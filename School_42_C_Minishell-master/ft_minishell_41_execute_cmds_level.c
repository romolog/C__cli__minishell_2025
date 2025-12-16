/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_41_execute_cmds_level.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:44:53 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:52:35 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_dup(int i, t_tr *t)
{
	int	k;

	if (i)
		ft_err(dup2(t->f_pipes[i - 1][0], STDIN_FILENO) == -1, \
					t, __FILE__, __LINE__);
	if (i != (t->cmd_num - 1))
		ft_err(dup2(t->f_pipes[i][1], STDOUT_FILENO) == -1, \
					t, __FILE__, __LINE__);
	k = -1;
	while (++k < t->cmd_num)
	{
		if (k < t->cmd_num -1)
		{
			ft_err(close(t->f_pipes[k][0]) == -1, t, __FILE__, __LINE__);
			ft_err(close(t->f_pipes[k][1]) == -1, t, __FILE__, __LINE__);
		}
	}
}

static void	ft_execute_cmds_levels_next(int encl, t_tkn **ptr_tkn)
{
	t_tkn	*tkn;

	if (!ptr_tkn || !*ptr_tkn)
		return ;
	tkn = *ptr_tkn;
	if ((!tkn->ao_and && !tkn->ao_or) || tkn->enclsr != encl)
	{
		while (tkn && !((tkn->brace_close || tkn->ao_and \
						|| tkn->ao_or) && tkn->enclsr == encl) \
					&& !(tkn->pipe && tkn->enclsr == encl))
			tkn = tkn->next;
		if (tkn && tkn->pipe && tkn->enclsr == encl)
			tkn = tkn->next;
	}
	*ptr_tkn = tkn;
}

void	ft_execute_cmds_levels(int i, int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;

	tkn = *ptr_tkn;
	t->f_pids[i] = fork();
	ft_err(t->f_pids[i] == -1, t, __FILE__, __LINE__);
	if (!t->f_pids[i])
	{
		t->pid_current = 0;
		ft_dup(i, t);
		if (tkn && tkn->brace_open)
		{
			tkn = tkn->next;
			ft_execute(encl + 1, tkn, t);
		}
		else
			ft_execute_pipe_child_cmd(&tkn, t);
	}
	ft_execute_cmds_levels_next(encl, &tkn);
	*ptr_tkn = tkn;
}
