/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_48_bltin_chdir_oldpwd_home_empty.c    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:39:08 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/05 19:40:41 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_call_chdir(int mode, t_tr *t)
{
	ft_free_str(&t->f_cwd_prev);
	ft_getenv(&t->f_cwd_prev, "PWD", t);
	if (mode)
	{
		write(1, t->f_chdir, ft_strlen(t->f_chdir));
		write(1, "\n", 1);
	}
	ft_err(chdir(t->f_chdir) == -1, t, __FILE__, __LINE__);
	ft_strlcpy(t->exit_les, "0", 2);
	ft_update_env("OLDPWD", t->f_cwd_prev, t);
	ft_update_env("PWD", t->f_chdir, t);
}

void	ft_chdir_oldpwd(int *condition, t_tkn *tkn, t_tr *t)
{
	if (*condition || !tkn || ft_strncmp(tkn->f_str, "-", 2))
		return ;
	*condition = 1;
	ft_free_str(&t->f_chdir);
	ft_getenv(&t->f_chdir, "OLDPWD", t);
	if (!t->f_chdir)
	{
		t->err = t->err_list->unset_oldpwd;
		ft_e(1, tkn->prev->f_str, NULL, t);
		t->exit_status = 1;
		ft_strlcpy(t->exit_les, "1", 2);
		return ;
	}
	if (ft_is_directory(t->f_chdir, t) == 1)
	{
		ft_call_chdir(1, t);
		return ;
	}
	t->err = t->err_list->no_file;
	ft_e(ft_is_directory(t->f_chdir, t) == -1, t->f_cmd, t->f_chdir, t);
	t->err = t->err_list->perm_denied;
	ft_e(ft_is_directory(t->f_chdir, t) - 1 == EACCES, \
								t->f_cmd, t->f_chdir, t);
	ft_strlcpy(t->exit_les, "1", 2);
}

void	ft_chdir_home(int *condition, t_tkn *tkn, t_tr *t)
{
	int		is_dir;

	if (*condition \
		|| (tkn && tkn->word && *tkn->f_str && ft_strncmp(tkn->f_str, "~", 2)))
		return ;
	*condition = 1;
	ft_free_str(&t->f_chdir);
	ft_getenv(&t->f_chdir, "HOME", t);
	ft_strlcpy(t->exit_les, "1", 2);
	t->err = t->err_list->unset_home;
	ft_e(!t->f_chdir, t->f_cmd, NULL, t);
	if (!t->f_chdir)
		return ;
	ft_strlcpy(t->exit_les, "0", 2);
	if (!*t->f_chdir)
		return ;
	ft_strlcpy(t->exit_les, "1", 2);
	t->err = t->err_list->no_file;
	is_dir = ft_is_directory(t->f_chdir, t);
	ft_e(is_dir == -1, t->f_cmd, t->f_chdir, t);
	t->err = t->err_list->perm_denied;
	ft_e(is_dir - 1 == EACCES, t->f_cmd, t->f_chdir, t);
	if (is_dir != 1)
		return ;
	ft_call_chdir(0, t);
}

// <cd ""> ONLY
// for <cd> or <cd~> check chdir home
void	ft_chdir_empty(int *condition, t_tkn *tkn, t_tr *t)
{
	if (*condition || !tkn || (tkn && *tkn->f_str))
		return ;
	*condition = 1;
	ft_free_str(&t->f_chdir);
	ft_getenv(&t->f_chdir, "PWD", t);
	ft_err(!t->f_chdir, t, __FILE__, __LINE__);
	ft_update_env("OLDPWD", t->f_chdir, t);
	ft_strlcpy(t->exit_les, "0", 2);
	return ;
}
