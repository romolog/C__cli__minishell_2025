/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_51_bltin_chdir_max_path.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:53:21 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:52 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_chdir_path_max(int *condition, char **f_curpath, t_tr *t)
{
	char	*f_str;
	size_t	len_cwd;
	size_t	len;

	if (*condition || !f_curpath || !*f_curpath)
		return ;
	ft_free_str(&t->f_cwd);
	t->f_cwd = getcwd(NULL, 0);
	ft_err(!t->f_cwd, t, __FILE__, __LINE__);
	len_cwd = ft_strlen(t->f_cwd);
	if (!ft_strncmp(*f_curpath, t->f_cwd, len_cwd))
	{
		f_str = NULL;
		len = ft_strlen(*f_curpath) - len_cwd;
		ft_add_str_malloc(&f_str, ".", 1, t);
		ft_add_str_malloc(&f_str, *f_curpath + len_cwd, len, t);
		ft_free_str(f_curpath);
		*f_curpath = f_str;
	}
}
