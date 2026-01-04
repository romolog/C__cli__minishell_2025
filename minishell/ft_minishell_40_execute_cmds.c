/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_40_execute_cmds.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:54:59 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:35:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_count_cmds(int encl, t_tkn *tkn, t_tr *t)
{
	t->cmd_num = 0;
	if (!t->tkn_head || !tkn)
		return ;
	while (tkn && !((tkn->brace_close || tkn->ao_and \
		|| tkn->ao_or) && tkn->enclsr == encl))
	{
		t->cmd_num += (tkn->pipe && tkn->enclsr == encl);
		tkn = tkn->next;
	}
	t->cmd_num++;
}

static void	ft_open_pipes(int ***pipes, t_tr *t)
{
	int		i;

	if (!t->pipes_num)
		return ;
	(*pipes) = malloc(t->pipes_num * sizeof(int *));
	ft_err(!(*pipes), t, __FILE__, __LINE__);
	i = -1;
	while (++i < t->pipes_num)
	{
		(*pipes)[i] = ft_calloc(2, sizeof(int));
		if (!(*pipes)[i])
		{
			while (--i >= 0)
			{
				ft_err(close((*pipes)[i][0]) == -1, t, __FILE__, __LINE__);
				ft_err(close((*pipes)[i][1]) == -1, t, __FILE__, __LINE__);
				ft_free_int((*pipes) + i);
			}
			free(*pipes);
			ft_err(1, t, __FILE__, __LINE__);
		}
		ft_err(pipe((*pipes)[i]) == -1, t, __FILE__, __LINE__);
	}
}

void	ft_close_pipes(int flag_read, int flag_write, int ***pipes, t_tr *t)
{
	int	i;

	i = -1;
	while (++i < t->pipes_num)
	{
		if (flag_read && (*pipes)[i][0] >= 0)
		{
			ft_err(close((*pipes)[i][0]) == -1, t, __FILE__, __LINE__);
			(*pipes)[i][0] = -1;
		}
		if (flag_write && (*pipes)[i][1] >= 0)
		{
			ft_err(close((*pipes)[i][1]) == -1, t, __FILE__, __LINE__);
			(*pipes)[i][1] = -1;
		}
	}
}

static void	ft_set_pids(t_tr *t)
{
	int	i;

	ft_free_int(&t->f_pids);
	t->f_pids = malloc(sizeof(int) * t->cmd_num);
	ft_err(!t->f_pids, t, __FILE__, __LINE__);
	i = -1;
	while (++i < t->cmd_num)
		t->f_pids[i] = -1;
}

void	ft_execute_pipe_cmds(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	extern sig_atomic_t		g_sig;
	t_tkn					*tkn;
	int						i;

	if (!t->tkn_head || !ptr_tkn)
		return ;
	tkn = *ptr_tkn;
	t->pipes_num = t->cmd_num - 1;
	ft_open_pipes(&t->f_pipes, t);
	ft_set_pids(t);
	i = -1;
	while (++i < t->cmd_num && !g_sig)
		ft_execute_cmds_levels(i, encl, &tkn, t);
	ft_close_pipes(1, 1, &t->f_pipes, t);
	ft_execute_pipe_catch_exit_status(i, t);
	ft_free_pipes(t);
	*ptr_tkn = tkn;
}
