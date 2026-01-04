/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_27_expand_var_heredoc.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:25:54 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 21:07:16 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_expand_variable(char **str, char **f_s, t_tr *t)
{
	char	*f_name;
	char	*f_value;
	int		i;

	if (str && *str && **str == '$')
	{
		(*str)++;
		i = 0;
		while ((*str)[i] && ((*str)[i] == '_' || \
			((*str)[i] >= 'a' && (*str)[i] <= 'z') || \
			((*str)[i] >= 'A' && (*str)[i] <= 'Z') || \
			((*str)[i] >= '0' && (*str)[i] <= '9')))
			i++;
		f_name = NULL;
		ft_add_str_malloc(&f_name, *str, i, t);
		f_value = NULL;
		ft_getenv(&f_value, f_name, t);
		ft_free_str(&f_name);
		if (f_value)
			ft_add_str_malloc(f_s, f_value, ft_strlen(f_value), t);
		ft_free_str(&f_value);
		(*str) += i;
	}
}

static void	ft_expand_var_hd_str(char **f_expanded, char **f_exp, t_tr *t)
{
	char	*str;
	char	*f_s;
	int		i;

	if (!f_exp || !*f_exp || !**f_exp)
		return ;
	f_s = NULL;
	str = *f_exp;
	while (str && *str)
	{
		i = 0;
		while (str[i] && !(str[i] == '$' && (str[i + 1] == '_' || \
			(str[i + 1] >= 'a' && str[i + 1] <= 'z') || \
			(str[i + 1] >= 'A' && str[i + 1] <= 'Z'))))
			i++;
		ft_add_str_malloc(&f_s, str, i, t);
		str += i;
		ft_expand_variable(&str, &f_s, t);
	}
	ft_free_str(f_exp);
	*f_exp = f_s;
	ft_add_str_malloc(f_expanded, *f_exp, ft_strlen(*f_exp), t);
}

static void	ft_expand_var_hd_replace(char *f_s, t_tkn *tkn, t_tr *t)
{
	int		fd;

	fd = open(tkn->f_str, O_WRONLY | O_TRUNC);
	ft_err(fd == -1, t, __FILE__, __LINE__);
	if (f_s)
		ft_err(write(fd, f_s, ft_strlen(f_s)) == -1, t, __FILE__, __LINE__);
	ft_err(close(fd) == 1, t, __FILE__, __LINE__);
}

void	ft_expand_var_heredoc(int encl, t_tkn *tkn, t_tr *t)
{
	char	*f_expanded;
	char	*f_exp;
	int		fd;

	while (t->tkn_head && tkn \
		&& (!tkn->redir_file_heredoc || !tkn->exp_env || tkn->enclsr != encl) \
		&& !tkn->brace_open && !tkn->brace_open && !tkn->pipe \
		&& !tkn->ao_and && !tkn->ao_or)
		tkn = tkn->next;
	if (!t->tkn_head || !tkn || tkn->brace_open || tkn->brace_open || tkn->pipe \
		|| tkn->ao_and || tkn->ao_or)
		return ;
	f_expanded = NULL;
	fd = open(tkn->f_str, O_RDONLY);
	ft_err(fd == -1, t, __FILE__, __LINE__);
	f_exp = ft_get_next_line(fd);
	while (f_exp)
	{
		ft_expand_var_hd_str(&f_expanded, &f_exp, t);
		ft_free_str(&f_exp);
		f_exp = ft_get_next_line(fd);
	}
	ft_err(close(fd) == 1, t, __FILE__, __LINE__);
	ft_expand_var_hd_replace(f_expanded, tkn, t);
	ft_free_str(&f_expanded);
}
