/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_17_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:05:03 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:20:44 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_tkn_quotes(int got_token, char **s, t_tr *t, t_tkn *tkn)
{
	int	done;

	if (got_token || !*s || !**s)
		return ;
	done = 0;
	done += ((**s == '\'' || **s == '\"') && !t->qd_on && !t->qs_on);
	tkn->exp_qd += (**s == '\"' && !t->qd_on && !t->qs_on);
	tkn->exp_qs += (**s == '\'' && !t->qd_on && !t->qs_on);
	t->qd_on += (**s == '\"' && !t->qd_on && !t->qs_on);
	t->qs_on += (**s == '\'' && !t->qd_on && !t->qs_on);
	done -= (!done && ((**s == '\"' && t->qd_on) || (**s == '\'' && t->qs_on)));
	t->qd_on -= (done == -1 && **s == '\"' && t->qd_on);
	t->qs_on -= (done == -1 && **s == '\'' && t->qs_on);
	if (done)
	{
		ft_add_str_malloc(&(tkn->f_str), *s, 1, t);
		tkn->word = 1;
		(*s)++;
	}
}

void	ft_tkn_redir_fd(int *got_token, char **s, t_tr *t, t_tkn *tkn)
{
	size_t	i;
	size_t	k;

	if (*got_token || !*s || !**s || t->qd_on || t->qs_on || tkn->word \
		|| **s < '0' || **s > '9')
		return ;
	i = 0;
	while ((*s)[i] == '0')
		i++;
	k = 0;
	while ((*s)[i + k] >= '0' && (*s)[i + k] <= '9')
		k++;
	if ((*s)[i + k] != '<' && (*s)[i + k] != '>')
		return ;
	ft_add_str_malloc(&(tkn->f_str), (*s) + i - (!k), k + (!k), t);
	tkn->w_redir_fd = 1;
	tkn->word = 1;
	*got_token = 1;
	(*s) += (i + k);
}

void	ft_tkn_operator_two(int *got_token, char **s, t_tr *t, t_tkn *tkn)
{
	int	cond;

	if (*got_token || !*s || !**s || t->qd_on || t->qs_on)
		return ;
	cond = (!ft_strncmp(*s, "<<", 2) || !ft_strncmp(*s, ">>", 2) \
		|| !ft_strncmp(*s, "&&", 2) || !ft_strncmp(*s, "||", 2));
	*got_token = cond;
	if (tkn->word || !cond)
		return ;
	tkn->ao_and += !ft_strncmp(*s, "&&", 2);
	tkn->ao_or += !ft_strncmp(*s, "||", 2);
	tkn->execute += 2 * (!ft_strncmp(*s, "||", 2) + !ft_strncmp(*s, "&&", 2));
	tkn->redir_input_heredoc += !ft_strncmp(*s, "<<", 2);
	tkn->redir_output_append += !ft_strncmp(*s, ">>", 2);
	if (cond)
	{
		ft_add_str_malloc(&(tkn->f_str), *s, 2, t);
		(*s) += 2;
		tkn->optr = 1;
	}
}

void	ft_tkn_operator_one(int *got_token, char **s, t_tr *t, t_tkn *tkn)
{
	int	condition;

	if (*got_token || !*s || !**s || t->qd_on || t->qs_on)
		return ;
	condition = (**s == '<' || **s == '>' || **s == '|' \
		|| **s == '(' || **s == ')');
	*got_token = condition;
	if (tkn->word || !condition)
		return ;
	tkn->redir_input += (**s == '<');
	tkn->redir_output_trunc += (**s == '>');
	tkn->pipe += (**s == '|');
	tkn->brace_open += (**s == '(');
	tkn->brace_close += (**s == ')');
	if (condition)
	{
		ft_add_str_malloc(&(tkn->f_str), *s, 1, t);
		(*s)++;
		tkn->optr = 1;
	}
}
