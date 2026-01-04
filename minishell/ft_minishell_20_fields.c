/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_20_fields.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:13:55 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 13:55:14 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_invalid_fields_andor(int *fail, t_tkn *tkn, t_tr *t)
{
	if (*fail)
		return ;
	while (!*fail && tkn)
	{
		if (tkn->ao_and || tkn->ao_or)
		{
			*fail += (!tkn->prev || tkn->prev->brace_open || tkn->prev->pipe \
				|| tkn->prev->redir_input || tkn->prev->redir_input_heredoc \
				|| tkn->prev->redir_output_append \
				|| tkn->prev->redir_output_trunc);
			*fail += (!tkn->next || tkn->next->ao_and || tkn->next->ao_or \
				|| tkn->next->brace_close || tkn->next->pipe);
		}
		tkn = tkn->next;
	}
	t->err = (t->err_list)->syntax_err;
	ft_e(*fail, "invalid and-or", NULL, t);
}

void	ft_invalid_fields_pipe(int *fail, t_tkn *tkn, t_tr *t)
{
	if (*fail)
		return ;
	while (!*fail && tkn)
	{
		if (tkn->pipe)
		{
			*fail += (!tkn->prev || tkn->prev->brace_open \
				|| tkn->prev->ao_and || tkn->prev->ao_or \
				|| tkn->prev->redir_input || tkn->prev->redir_input_heredoc \
				|| tkn->prev->redir_output_append \
				|| tkn->prev->redir_output_trunc);
			*fail += (!tkn->next || tkn->next->pipe \
				|| tkn->next->brace_close \
				|| tkn->next->ao_and || tkn->next->ao_or);
		}
		tkn = tkn->next;
	}
	t->err = (t->err_list)->syntax_err;
	ft_e(*fail, "invalid pipe", NULL, t);
}

void	ft_invalid_fields_redirection(int *fail, t_tkn *tkn, t_tr *t)
{
	if (*fail)
		return ;
	while (!*fail && tkn)
	{
		if (tkn->redir_input || tkn->redir_input_heredoc \
			|| tkn->redir_output_append || tkn->redir_output_trunc)
			*fail += (!tkn->next || !tkn->next->word);
		tkn = tkn->next;
	}
	t->err = (t->err_list)->syntax_err;
	ft_e(*fail, "invalid redirection", NULL, t);
}
