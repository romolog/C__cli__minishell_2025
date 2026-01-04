/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_18_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:05:03 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:20:52 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_tkn_delimiter(int *got_token, char **s, t_tr *t, t_tkn *tkn)
{
	size_t	i;

	if (*got_token || !*s || !**s)
	{
		if (!**s && tkn->word != 0)
			*got_token = 1;
		return ;
	}
	if ((**s == ' ' || **s == '\t') && (t->qd_on || t->qs_on))
	{
		i = 0;
		while ((*s)[i] == ' ' || (*s)[i] == '\t')
			i++;
		ft_add_str_malloc(&(tkn->f_str), *s, i, t);
		(*s) += i;
	}
	else if (**s == ' ' || **s == '\t')
	{
		*got_token = (tkn->word != 0);
		while (**s == ' ' || **s == '\t')
			(*s)++;
	}
}

void	ft_tkn_word_quoted(int got_token, char **s, t_tr *t, t_tkn *tkn)
{
	size_t	i;

	if (got_token || !*s || !**s || (!t->qd_on && !t->qs_on))
		return ;
	i = -1;
	while ((*s)[++i] \
		&& (((*s)[i] != '\"' && t->qd_on) || ((*s)[i] != '\'' && t->qs_on)))
	{
		if (!t->qs_on && (!tkn->prev || !tkn->prev->redir_input_heredoc) \
			&& (*s)[i] == '$' && ((*s)[i + 1] == '_' \
				|| ((*s)[i + 1] >= 'a' && (*s)[i + 1] <= 'z') \
				|| ((*s)[i + 1] >= 'A' && (*s)[i + 1] <= 'Z')))
			tkn->exp_env = 1;
		else if (!t->qs_on && (*s)[i] == '$' && (*s)[i + 1] == '?')
			tkn->exp_les = 1;
		else if (!t->qs_on && (*s)[i] == '$' && (*s)[i + 1] != '\0')
			tkn->exp_inv = 1;
	}
	ft_add_str_malloc(&(tkn->f_str), *s, i, t);
	(*s) += i;
}

void	ft_tkn_word_unquoted(int got_token, char **s, t_tr *t, t_tkn *tkn)
{
	size_t	i;

	if (got_token || !*s || !**s || t->qd_on || t->qs_on \
		|| **s == ' ' || **s == '\t' || **s == '\"' || **s == '\'' \
		|| **s == '>' || **s == '<' || **s == '|' || **s == '(' || **s == ')' \
		|| !ft_strncmp(*s, "&&", 2) || !ft_strncmp(*s, "||", 2))
		return ;
	tkn->word += (!tkn->word);
	i = -1;
	while ((*s)[++i] && (*s)[i] != ' ' && (*s)[i] != '\t' \
		&& (*s)[i] != '\"' && (*s)[i] != '\'' \
		&& (*s)[i] != ' ' && (*s)[i] != '\t' \
		&& (*s)[i] != '>' && (*s)[i] != '<' && (*s)[i] != '|' \
		&& (*s)[i] != '(' && (*s)[i] != ')' \
		&& ft_strncmp((*s) + i, "&&", 2) && ft_strncmp((*s) + i, "||", 2))
	{
		tkn->exp_env += ((*s)[i] == '$' && (*s)[i + 1] != '?');
		tkn->exp_les += ((*s)[i] == '$' && (*s)[i + 1] == '?');
		tkn->exp_wldcrd += ((*s)[i] == '*');
	}
	ft_add_str_malloc(&(tkn->f_str), *s, i, t);
	(*s) += i;
}
