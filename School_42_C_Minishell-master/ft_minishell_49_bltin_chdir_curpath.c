/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_49_bltin_chdir_curpath.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:41:18 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:50:00 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_find_path(char **f_curpath, t_tkn *tkn, t_tr *t)
{
	char	**f_p;
	char	*f_s;
	int		i;

	f_p = ft_split(t->f_path, ':');
	ft_err(!f_p, t, __FILE__, __LINE__);
	f_s = NULL;
	i = -1;
	while (ft_is_directory(f_s, t) < 0 && f_p[++i])
	{
		ft_free_str(&f_s);
		ft_add_str_malloc(&f_s, f_p[i], ft_strlen(f_p[i]), t);
		if (f_s[ft_strlen(f_s) - 1] != '/')
			ft_add_str_malloc(&f_s, "/", 1, t);
		ft_add_str_malloc(&f_s, tkn->f_str, ft_strlen(tkn->f_str), t);
	}
	if (ft_is_directory(f_s, t) <= 0)
	{
		ft_free_str(&f_s);
		ft_free_str(f_curpath);
	}
	ft_free_2d_char(&f_p);
	*f_curpath = f_s;
}

static void	ft_cat_cwd_curpath(char **f_curpath, t_tr *t)
{
	char	*f_str;

	f_str = NULL;
	ft_free_str(&t->f_cwd);
	t->f_cwd = getcwd(NULL, 0);
	ft_add_str_malloc(&f_str, t->f_cwd, ft_strlen(t->f_cwd), t);
	if (f_str[ft_strlen(f_str) - 1] != '/')
		ft_add_str_malloc(&f_str, "/", 1, t);
	ft_add_str_malloc(&f_str, *f_curpath, ft_strlen(*f_curpath), t);
	ft_free_str(f_curpath);
	*f_curpath = f_str;
}

void	ft_chdir_set_curpath(int *cond, char **f_curpath, t_tkn *tkn, t_tr *t)
{
	if (*cond || !tkn || !ft_strncmp(tkn->f_str, "~", 2))
		return ;
	ft_free_str(&t->f_home);
	ft_getenv(&t->f_home, "HOME=", t);
	if (tkn->f_str[0] == '/' || tkn->f_str[0] == '.')
		ft_add_str_malloc(f_curpath, tkn->f_str, ft_strlen(tkn->f_str), t);
	else
	{
		ft_free_str(&t->f_path);
		ft_getenv(&t->f_path, "PATH", t);
		if (!t->f_path)
		{
			ft_add_str_malloc(f_curpath, "./", 2, t);
			ft_add_str_malloc(f_curpath, tkn->f_str, ft_strlen(tkn->f_str), t);
		}
		else
			ft_find_path(f_curpath, tkn, t);
	}
	if (!*f_curpath)
		ft_add_str_malloc(f_curpath, tkn->f_str, ft_strlen(tkn->f_str), t);
	if ((*f_curpath)[0] != '/')
		ft_cat_cwd_curpath(f_curpath, t);
	ft_chdir_canon_curpath(cond, f_curpath, t);
	ft_chdir_path_max(cond, f_curpath, t);
}
