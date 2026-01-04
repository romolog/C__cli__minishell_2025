/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_35_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:50:38 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/06 14:06:30 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_passby_to_cmd(t_tkn **ptr_tkn)
{
	while (*ptr_tkn && \
		((*ptr_tkn)->w_redir_fd \
		|| (*ptr_tkn)->redir_input || (*ptr_tkn)->redir_input_heredoc \
		|| (*ptr_tkn)->redir_output_append || (*ptr_tkn)->redir_output_trunc \
		|| (*ptr_tkn)->w_redir_file || (*ptr_tkn)->redir_file_heredoc))
		*ptr_tkn = (*ptr_tkn)->next;
}

static int	ft_do_redir(t_tkn *tkn, t_tr *t)
{
	int		redir_error;

	redir_error = 0;
	while (!redir_error && tkn && !tkn->ao_and && !tkn->ao_or \
		&& !tkn->brace_close && !tkn->pipe)
	{
		if (tkn->redir_input \
			|| tkn->redir_output_append || tkn->redir_output_trunc)
		{
			t->tkn_tracer = tkn;
			if (tkn->redir_input)
				redir_error = ft_redir_file(STDIN_FILENO, tkn->next, t);
			else
				redir_error = ft_redir_file(STDOUT_FILENO, tkn->next, t);
			tkn = t->tkn_tracer;
		}
		else
			tkn = tkn->next;
	}
	return (redir_error);
}

int	ft_redir(t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;
	int		redir_error;

	if (!ptr_tkn)
		return (-1);
	if (!t->tkn_head || !*ptr_tkn)
		return (0);
	tkn = *ptr_tkn;
	ft_passby_to_cmd(ptr_tkn);
	redir_error = ft_do_redir(tkn, t);
	if (redir_error)
	{
		t->exit_status = 1;
		ft_strlcpy(t->exit_les, "1", 2);
	}
	return (redir_error);
}
