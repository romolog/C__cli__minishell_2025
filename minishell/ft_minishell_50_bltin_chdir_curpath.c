/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_50_bltin_chdir_curpath.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:39:08 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/05 19:41:35 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_start_curpath(char **f_new, char **ptr, t_tr *t)
{
	if (**ptr == '/')
		ft_add_str_malloc(f_new, "/", 1, t);
}

static void	ft_stop_curpath(int *cond, char *f_new, t_tr *t)
{
	int		dir_check;

	dir_check = ft_is_directory(f_new, t);
	if (dir_check == 1 || dir_check - 1 == EACCES)
		return ;
	*cond = 1;
	ft_strlcpy(t->exit_les, "1", 2);
	t->err = t->err_list->not_dir;
	ft_e(!dir_check, t->f_cmd, t->f_chdir, t);
	t->err = t->err_list->no_file;
	ft_e(dir_check == -1, t->f_cmd, t->f_chdir, t);
}

static void	ft_delete_component_curpath(char **f_new, char *str, t_tr *t)
{
	char	*f_s;
	int		len;

	if (!str || !f_new || !*f_new || !ft_strncmp(*f_new, "/", 2))
		return ;
	len = ft_strlen(*f_new);
	len--;
	while (len && (*f_new)[len - 1] != '/')
		len --;
	f_s = NULL;
	ft_add_str_malloc(&f_s, *f_new, len, t);
	ft_free_str(f_new);
	*f_new = f_s;
}

static void	ft_parse_curpath(int *cond, char **f_new, char *str, t_tr *t)
{
	if (*cond || !str)
		return ;
	if (!ft_strncmp(str, ".", 2))
		return ;
	else if (!ft_strncmp(str, "..", 3))
		ft_delete_component_curpath(f_new, str, t);
	else
	{
		ft_add_str_malloc(f_new, str, ft_strlen(str), t);
		ft_add_str_malloc(f_new, "/", 1, t);
		ft_stop_curpath(cond, *f_new, t);
	}
}

void	ft_chdir_canon_curpath(int *condition, char **f_curpath, t_tr *t)
{
	int		i;
	char	*f_new;
	char	**f_arr;

	if (*condition || !f_curpath || !*f_curpath)
		return ;
	f_new = NULL;
	ft_start_curpath(&f_new, f_curpath, t);
	f_arr = ft_split(*f_curpath, '/');
	ft_free_str(f_curpath);
	ft_err(!f_arr, t, __FILE__, __LINE__);
	i = -1;
	while (!*condition && f_arr[++i])
		ft_parse_curpath(condition, &f_new, f_arr[i], t);
	*f_curpath = f_new;
	ft_free_2d_char(&f_arr);
	if (!*condition)
	{
		*condition += (ft_is_directory(*f_curpath, t) - 1 == EACCES);
		t->err = t->err_list->perm_denied;
		ft_e(*condition, t->f_cmd, t->f_chdir, t);
	}
	if (*condition)
		ft_free_str(f_curpath);
}
