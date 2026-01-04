/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_21_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:04:30 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/08 21:23:02 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_unlink_heredoc(t_tr *t)
{
	int		k;
	char	*f_fd;

	f_fd = NULL;
	while (ft_strncmp(t->hd_filename, t->hd_filename_0, \
							ft_strlen(t->hd_filename_0)))
	{
		ft_err(unlink(t->hd_filename) == -1, t, __FILE__, __LINE__);
		k = ft_atoi(t->hd_filename + ft_strlen(t->hd_filemask)) - 1;
		f_fd = ft_itoa(k);
		ft_strlcpy(t->hd_filename + ft_strlen(t->hd_filemask), f_fd, \
					ft_strlen(f_fd) + 1);
		ft_free_str(&f_fd);
	}
	ft_free_str(&f_fd);
}

static void	ft_replace_heredoc_token(t_tkn *tkn, t_tr *t)
{
	t_tkn	*lim;
	char	*fname;

	if (!t->tkn_head || !tkn)
		return ;
	lim = tkn->next;
	ft_free_str(&lim->f_str);
	fname = t->hd_filename;
	ft_add_str_malloc(&lim->f_str, fname, ft_strlen(fname), t);
	lim->w_redir_lim = 0;
	lim->redir_file_heredoc = 1;
	tkn->redir_input_heredoc = 0;
	tkn->redir_input = 1;
}

static void	ft_set_lim_fstr(char **lim, t_tkn *tkn, t_tr *t)
{
	char	*f_exp;
	char	*exp;

	f_exp = NULL;
	tkn->exp_env = (ft_strchr(tkn->f_str, '\"') == NULL \
		&& ft_strchr(tkn->f_str, '\'') == NULL);
	ft_add_str_malloc(&f_exp, tkn->f_str, ft_strlen(tkn->f_str), t);
	exp = f_exp;
	ft_reset_qds(t);
	ft_free_str(&tkn->f_str);
	while (*exp)
	{
		exp += ft_quotes_status(exp, t);
		exp += ft_expand_quotes_parse(exp, &tkn->f_str, t);
	}
	ft_free_str(&f_exp);
	*lim = tkn->f_str;
}

int	ft_heredoc_all(t_tr *t)
{
	char			*lim;

	ft_signal_all_ignore(t);
	lim = NULL;
	t->exit_status = 0;
	t->tkn_heredoc_tracer = t->tkn_head;
	while (t->tkn_heredoc_tracer)
	{
		if (t->tkn_heredoc_tracer->redir_input_heredoc)
		{
			ft_heredoc_file("name", t);
			ft_set_lim_fstr(&lim, t->tkn_heredoc_tracer->next, t);
			ft_err(!lim, t, __FILE__, __LINE__);
			ft_heredoc_fork_readfile(lim, t);
			ft_heredoc_if_sigint(t);
			ft_heredoc_file("close", t);
			ft_replace_heredoc_token(t->tkn_heredoc_tracer, t);
		}
		if (t->tkn_heredoc_tracer)
			t->tkn_heredoc_tracer = t->tkn_heredoc_tracer->next;
	}
	return (t->exit_status);
}
