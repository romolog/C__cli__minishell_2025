/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_42_execute_pipe_cmd.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:14:12 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:52:57 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_start_execute_cmd(t_tkn *tkn, t_tr *t)
{
	if (tkn && tkn->word)
	{
		ft_free_str(&t->f_cmd);
		ft_add_str_malloc(&t->f_cmd, tkn->f_str, ft_strlen(tkn->f_str), t);
		ft_free_str(&t->f_cmd_path);
		ft_add_str_malloc(&t->f_cmd_path, tkn->f_str, \
							ft_strlen(tkn->f_str), t);
	}
	ft_close_catched_stds(t);
}

static void	ft_execute_pipe_child_cmd_empty_tkn(t_tkn *tkn, t_tr *t)
{
	if (tkn && tkn->word)
		return ;
	t->do_exit = 1;
	t->exit_status = 0;
	ft_free_all(t);
}

static void	ft_execute_pipe_child_cmd_blanc_str(char *str, t_tr *t)
{
	int		is_blanc;

	is_blanc = ft_is_blanc_str(str);
	if (!is_blanc)
		return ;
	ft_err(is_blanc < 0, t, __FILE__, __LINE__);
	t->do_exit = 1;
	t->exit_status = 127;
	if (is_blanc == 1)
	{
		t->err = t->err_list->cmd_notfound;
		ft_e(1, "empty string", NULL, t);
	}
	else if (is_blanc > 1)
	{
		t->err = t->err_list->cmd_notfound;
		ft_e(1, "blanc string", NULL, t);
	}
	ft_free_all(t);
}

static void	ft_execute_pipe_child_cmd_builtin(t_tkn *tkn, t_tr *t)
{
	if (ft_execute_builtin(tkn, t))
	{
		t->do_exit = 1;
		t->exit_status = ft_atoi(t->exit_les);
		ft_free_all(t);
	}
}

void	ft_execute_pipe_child_cmd(t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;
	int		redir_error;

	redir_error = ft_redir(ptr_tkn, t);
	if (t->tkn_head && ptr_tkn && !redir_error)
	{
		tkn = *ptr_tkn;
		ft_start_execute_cmd(tkn, t);
		ft_execute_pipe_child_cmd_empty_tkn(tkn, t);
		ft_execute_pipe_child_cmd_blanc_str(tkn->f_str, t);
		ft_execute_pipe_child_cmd_builtin(tkn, t);
		ft_execute_pipe_child_cmd_call_execve(&tkn, t);
	}
	t->do_exit = 1;
	t->exit_status += 1 * (!t->exit_status);
	ft_free_all(t);
}
