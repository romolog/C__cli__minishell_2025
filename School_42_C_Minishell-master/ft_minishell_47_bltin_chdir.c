/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_47_bltin_chdir.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:41:18 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:50:09 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// is invalid if more than 1 arg
static int	ft_chdir_invalid_args(int *condition, t_tkn *tkn, t_tr *t)
{
	if (!t->tkn_head || !tkn)
		return (0);
	ft_strlcpy(t->exit_les, "0", 2);
	if (tkn && tkn->word && tkn->next \
		&& tkn->next->word && !tkn->next->w_redir_fd)
	{
		*condition = 1;
		ft_strlcpy(t->exit_les, "1", 2);
		t->err = t->err_list->many_args;
		ft_e(1, tkn->prev->f_str, NULL, t);
		return (1);
	}
	return (0);
}

static void	ft_set_exit_chdir(int cd_check, t_tr *t)
{
	if (cd_check != -1)
	{
		ft_strlcpy(t->exit_les, "0", 2);
		t->exit_status = 0;
		ft_update_env("OLDPWD=", t->f_cwd_prev, t);
		ft_free_str(&t->f_cwd);
		t->f_cwd = getcwd(NULL, 0);
		ft_err(!t->f_cwd, t, __FILE__, __LINE__);
		ft_update_env("PWD=", t->f_cwd, t);
		return ;
	}
	ft_strlcpy(t->exit_les, "1", 2);
	t->exit_status = 1;
}

static void	ft_call_chdir(int condition, char *f_curpath, t_tr *t)
{
	int		cd_check;

	if (condition)
		return ;
	if (f_curpath)
	{
		ft_free_str(&t->f_cwd_prev);
		t->f_cwd_prev = getcwd(NULL, 0);
		ft_err(!t->f_cwd_prev, t, __FILE__, __LINE__);
		cd_check = chdir(f_curpath);
		ft_set_errno_messages(errno, t);
		ft_e(cd_check == -1, t->f_cmd, f_curpath, t);
		ft_set_exit_chdir(cd_check, t);
		ft_free_str(&f_curpath);
	}
	else
	{
		t->exit_status = 0;
		ft_strlcpy(t->exit_les, "0", 2);
	}
}

void	ft_bltin_chdir(t_tkn *tkn, t_tr *t)
{
	char	*f_curpath;
	int		condition;

	if (!t->tkn_head || !tkn || ft_strncmp(tkn->f_str, "cd", 3))
		return ;
	ft_free_str(&t->f_cmd);
	ft_add_str_malloc(&t->f_cmd, "cd", 2, t);
	t->exit_status = 0;
	tkn = tkn->next;
	condition = 0;
	ft_chdir_invalid_args(&condition, tkn, t);
	ft_chdir_empty(&condition, tkn, t);
	ft_chdir_home(&condition, tkn, t);
	ft_chdir_oldpwd(&condition, tkn, t);
	if (condition)
		return ;
	f_curpath = NULL;
	ft_free_str(&t->f_chdir);
	ft_add_str_malloc(&t->f_chdir, tkn->f_str, ft_strlen(tkn->f_str), t);
	ft_chdir_set_curpath(&condition, &f_curpath, tkn, t);
	ft_call_chdir(condition, f_curpath, t);
	ft_free_str(&t->f_cmd);
}
