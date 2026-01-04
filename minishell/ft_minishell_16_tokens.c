/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_16_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:56:47 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/08 19:11:12 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_set_token(t_tkn *new_tkn, t_tr *t)
{
	new_tkn->next = NULL;
	if (!t->tkn_head)
	{
		t->tkn_head = new_tkn;
		new_tkn->prev = NULL;
	}
	else if (t->tkn_head)
	{
		t->tkn_tracer->next = new_tkn;
		new_tkn->prev = t->tkn_tracer;
	}
	t->tkn_tracer = new_tkn;
	new_tkn->f_str = NULL;
	new_tkn->enclsr = -1;
}

static void	ft_malloc_tkn(t_tr *t)
{
	t_tkn	*new_tkn;

	new_tkn = ft_calloc(1, sizeof(t_tkn));
	ft_err(!new_tkn, t, __FILE__, __LINE__);
	ft_set_token(new_tkn, t);
}

static void	ft_get_tkn(char **str, t_tr *t)
{
	int	got_token;

	ft_reset_qds(t);
	got_token = 0;
	while (*str && **str && !got_token)
	{
		ft_tkn_quotes(got_token, str, t, t->tkn_tracer);
		ft_tkn_redir_fd(&got_token, str, t, t->tkn_tracer);
		ft_tkn_operator_two(&got_token, str, t, t->tkn_tracer);
		ft_tkn_operator_one(&got_token, str, t, t->tkn_tracer);
		ft_tkn_word_quoted(got_token, str, t, t->tkn_tracer);
		ft_tkn_word_unquoted(got_token, str, t, t->tkn_tracer);
		ft_tkn_delimiter(&got_token, str, t, t->tkn_tracer);
	}
}

static void	ft_if_rest_str_blanc(char **str)
{
	char	*s;

	if (!str || !*str || !**str)
		return ;
	s = *str;
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (!*s)
		*str = s;
}

void	ft_get_tokens(t_tr *t)
{
	char	*s;

	t->token_qty = 0;
	s = t->f_line;
	while (s && *s && (*s == ' ' || *s == '\t'))
		s++;
	if (!*s)
	{
		t->exit_status = 0;
		ft_strlcpy(t->exit_les, "0", 2);
		return ;
	}
	while (s && *s && ++t->token_qty)
	{
		ft_malloc_tkn(t);
		ft_get_tkn(&s, t);
		ft_reset_qds(t);
		ft_if_rest_str_blanc(&s);
	}
}
