/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_24_execute_pipe.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:58:17 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 14:34:31 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// RETURN: 
//		-2	cmd >1 or head is NULL
//		-1	only redirection
//		1	single builtin
//		0	not builtin
static int	ft_is_single_builtin_redir(t_tkn *tkn, t_tr *t)
{
	int	encl;
	int	builtin;

	if (!t->tkn_head || !tkn || t->cmd_num != 1)
		return (-2);
	encl = tkn->enclsr;
	builtin = 0;
	while (tkn && (tkn->w_redir_fd || tkn->w_redir_file \
		|| tkn->redir_file_heredoc || tkn->redir_input \
		|| tkn->redir_output_append || tkn->redir_output_trunc) \
		&& tkn->enclsr == encl)
		tkn = tkn->next;
	if (tkn && tkn->enclsr == encl && tkn->word)
		builtin += (!builtin) * ft_is_builtin(tkn->f_str);
	else if (!tkn)
		builtin = -1;
	return (builtin);
}

void	ft_expand_assign_tags(int encl, t_tkn *tkn, t_tr *t)
{
	int	cmd;

	if (!t->tkn_head || !tkn)
		return ;
	cmd = 0;
	while (tkn && !((tkn->brace_close || tkn->ao_and \
		|| tkn->ao_or) && tkn->enclsr == encl))
	{
		if (tkn->prev && (tkn->prev->redir_input \
			|| tkn->prev->redir_output_append || tkn->prev->redir_output_trunc))
			tkn->w_redir_file = (!tkn->redir_file_heredoc);
		if (tkn->enclsr == encl && tkn->word && !tkn->w_redir_fd \
			&& !tkn->redir_file_heredoc && !tkn->w_redir_file && !cmd)
		{
			tkn->w_bltin = ft_is_builtin(tkn->f_str);
			tkn->w_cmd = !tkn->w_bltin;
			cmd = 1;
		}
		else if (tkn->enclsr == encl && tkn->word && !tkn->w_redir_fd && cmd)
			tkn->w_arg = 1;
		if (tkn->pipe)
			cmd = 0;
		tkn = tkn->next;
	}
}

static void	ft_call_single_builtin(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;

	if (!ft_redir(ptr_tkn, t))
		ft_execute_builtin(*ptr_tkn, t);
	ft_signal_handler_sigint_main(t);
	ft_signal_handler_sigquit_main(t);
	ft_redir_close_files(t);
	ft_reset_std(t);
	tkn = *ptr_tkn;
	while (t->tkn_head && tkn && !tkn->brace_close && !tkn->brace_open \
	&& !tkn->ao_and && !tkn->ao_or && !tkn->pipe && tkn->enclsr == encl)
		tkn = tkn->next;
	*ptr_tkn = tkn;
}

static int	ft_execute_pipe_start(int encl, t_tkn **tkn, t_tr *t)
{
	if (!t->tkn_head || !tkn || (*tkn && ((*tkn)->ao_and || (*tkn)->ao_or)))
		return (0);
	ft_free_pipes(t);
	ft_expand_var(encl, tkn, t);
	ft_expand_split(encl, tkn, t);
	if (t->tkn_head && tkn && \
		(!*tkn || (*tkn)->ao_and || (*tkn)->ao_or || (*tkn)->brace_close))
		return (1);
	if (!t->tkn_head || !tkn)
		return (0);
	ft_expand_wildcards(encl, *tkn, t);
	ft_expand_quotes(encl, *tkn, t);
	ft_expand_assign_tags(encl, *tkn, t);
	ft_count_cmds(encl, *tkn, t);
	return (1);
}

void	ft_execute_pipe(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;

	if (!ft_execute_pipe_start(encl, ptr_tkn, t))
		return ;
	tkn = *ptr_tkn;
	if (ft_is_single_builtin_redir(tkn, t) > 0)
		ft_call_single_builtin(encl, &tkn, t);
	else if (ft_is_single_builtin_redir(tkn, t) == -1)
	{
		ft_redir(&tkn, t);
		ft_redir_close_files(t);
		ft_reset_std(t);
		ft_move_next_execute(encl, &tkn);
	}
	else if (t->tkn_head)
		ft_execute_pipe_cmds(encl, &tkn, t);
	*ptr_tkn = tkn;
}
