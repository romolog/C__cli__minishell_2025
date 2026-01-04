/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_37_redir_delete_tkns.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:15:54 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/11 17:42:39 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_set_tkn_prv_nxt(t_tkn **prv, t_tkn **nxt, t_tkn **tkn, t_tr *t)
{
	if (*prv && (*prv)->w_redir_fd)
	{
		*tkn = *prv;
		*prv = (*prv)->prev;
	}
	if (!*prv && !*nxt)
	{
		t->do_exit = (!t->pid_current);
		if (t->do_exit)
			ft_free_all(t);
		ft_free_tokens(t);
		ft_free_int(&t->f_pids);
		ft_free_2d_int(&t->f_pipes);
		if (t->f_cmd_args)
		{
			free(t->f_cmd_args);
			t->f_cmd_args = NULL;
		}
	}
	if (!*prv)
		t->tkn_head = *nxt;
	if (*prv)
		(*prv)->next = *nxt;
	if (*nxt)
		(*nxt)->prev = *prv;
}

void	ft_redir_delete_tkns(t_tkn *tkn, t_tr *t)
{
	t_tkn	*prv;
	t_tkn	*nxt;
	t_tkn	*temp;

	prv = tkn->prev;
	nxt = tkn->next->next;
	ft_set_tkn_prv_nxt(&prv, &nxt, &tkn, t);
	if (!t->tkn_head)
		return ;
	temp = tkn->next;
	ft_free_str(&tkn->f_str);
	free(tkn);
	tkn = temp->next;
	ft_free_str(&temp->f_str);
	free(temp);
	if (tkn && (tkn->redir_file_heredoc || tkn->w_redir_file))
	{
		ft_free_str(&tkn->f_str);
		free(tkn);
	}
	t->tkn_tracer = nxt;
}

int	ft_is_valid_redir_directory(t_tkn *tkn, t_tr *t)
{
	int		is_dir;
	char	*ptr;
	char	*f_dir;

	ptr = ft_strrchr(tkn->f_str, '/');
	if (!ptr)
		return (1);
	f_dir = NULL;
	ft_add_str_malloc(&f_dir, tkn->f_str, ptr - tkn->f_str, t);
	is_dir = ft_is_directory(f_dir, t);
	ft_free_str(&f_dir);
	if (is_dir == 1 && ptr[1])
		return (1);
	if (!ptr[1])
		t->err = t->err_list->is_dir;
	else if (is_dir <= 0)
		t->err = t->err_list->not_dir;
	else if (is_dir - 1 == EACCES)
		t->err = t->err_list->perm_denied;
	ft_e(1, tkn->f_str, NULL, t);
	return (0);
}

//	must recheck dir, after recheck all dir included in the path
int	ft_is_valid_file_path(t_tkn *tkn, t_tr *t)
{
	if (ft_is_directory(tkn->f_str, t) >= 1)
	{
		t->err = t->err_list->is_dir;
		ft_e(1, tkn->f_str, NULL, t);
		return (1);
	}
	else if (!access(tkn->f_str, F_OK) && !access(tkn->f_str, W_OK))
		return (1);
	else if (access(tkn->f_str, F_OK))
		return (1);
	else
	{
		t->err = t->err_list->perm_denied;
		ft_e(1, tkn->f_str, NULL, t);
		return (0);
	}
}
