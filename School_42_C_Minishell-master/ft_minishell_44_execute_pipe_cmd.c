/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_44_execute_pipe_cmd.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:52:39 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/10 21:39:19 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_stop_curpath(int *cond, char *f_new, t_tr *t)
{
	int		dir_check;

	dir_check = ft_is_directory(f_new, t);
	if (dir_check == 1 || dir_check == EACCES)
		return ;
	if (!dir_check && !access(f_new, F_OK))
		return ;
	*cond = 1;
	if (!dir_check)
	{
		t->exit_status = 126;
		ft_strlcpy(t->exit_les, "126", 4);
		t->err = t->err_list->not_dir;
	}
	else if (dir_check == -1)
	{
		t->exit_status = 127;
		ft_strlcpy(t->exit_les, "127", 4);
		t->err = t->err_list->no_file;
	}
	ft_e(1, t->f_cmd, NULL, t);
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
		ft_add_str_malloc(f_new, str, ft_strlen(str), t);
}

void	ft_cmd_canon_curpath(int *condition, char **f_p, t_tr *t)
{
	int		i;
	char	*f_new;
	char	**f_arr;

	if (*condition || !f_p || !*f_p)
		return ;
	f_new = NULL;
	if (**f_p == '/' || !ft_strncmp(*f_p, "./", 2))
		ft_add_str_malloc(&f_new, *f_p, 1 + !ft_strncmp(*f_p, "./", 2), t);
	f_arr = ft_split(*f_p, '/');
	ft_err(!f_arr, t, __FILE__, __LINE__);
	i = -1;
	while (!*condition && f_arr[++i])
	{
		ft_parse_curpath(condition, &f_new, f_arr[i], t);
		if (f_arr[i + 1] || (*f_p)[ft_strlen(*f_p) - 1] == '/')
			ft_add_str_malloc(&f_new, "/", 1, t);
		ft_stop_curpath(condition, f_new, t);
	}
	ft_free_str(f_p);
	*f_p = f_new;
	ft_free_2d_char(&f_arr);
	if (*condition)
		ft_free_str(f_p);
}

void	ft_execute_pipe_child_simplify_path(t_tr *t)
{
	int		condition;

	condition = 0;
	if (*t->f_cmd_path != '/' && ft_strncmp(t->f_cmd_path, "./", 2))
		return ;
	ft_cmd_canon_curpath(&condition, &t->f_cmd_path, t);
	if (!condition)
	{
		condition += (ft_is_directory(t->f_cmd_path, t) == EACCES);
		t->err = t->err_list->perm_denied;
		ft_e(condition, t->f_cmd, t->f_chdir, t);
	}
	if (condition)
	{
		t->do_exit = 1;
		t->exit_status += 1 * (!t->exit_status);
		ft_free_all(t);
	}
}
