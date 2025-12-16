/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_32_cwd_filenames.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:42:41 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/03 21:25:44 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_count_cwd_files_dir(char *f_cwd, t_tr *t)
{
	int				count;
	DIR				*dir_cwd;
	struct dirent	*entry;

	count = 0;
	dir_cwd = opendir(f_cwd);
	ft_err(!dir_cwd, t, __FILE__, __LINE__);
	errno = 0;
	entry = readdir(dir_cwd);
	ft_err(errno, t, __FILE__, __LINE__);
	while (entry)
	{
		if (entry->d_type == DT_REG || entry->d_type == DT_DIR)
			count++;
		entry = readdir(dir_cwd);
		ft_err(errno, t, __FILE__, __LINE__);
	}
	ft_err(closedir(dir_cwd) == -1, t, __FILE__, __LINE__);
	return (count);
}

static void	ft_fn(int names_num, char **fn, struct dirent *entry, t_tr *t)
{
	fn[names_num] = malloc(ft_strlen(entry->d_name) + 1);
	if (!fn[names_num])
	{
		ft_free_2d_char(&fn);
		ft_err(1, t, __FILE__, __LINE__);
	}
	ft_strlcpy(fn[names_num], entry->d_name, ft_strlen(entry->d_name) + 1);
}

static void	ft_put_cwd_filename(int names_num, char **fn, char *f_cwd, t_tr *t)
{
	DIR				*dir_cwd;
	struct dirent	*entry;
	int				done;

	dir_cwd = opendir(f_cwd);
	ft_err(!dir_cwd, t, __FILE__, __LINE__);
	while (names_num--)
	{
		done = 0;
		while (!done)
		{
			errno = 0;
			entry = readdir(dir_cwd);
			ft_err(errno, t, __FILE__, __LINE__);
			if (entry->d_type == DT_REG || entry->d_type == DT_DIR)
				ft_fn(names_num, fn, entry, t);
			done += (entry->d_type == DT_REG || entry->d_type == DT_DIR);
		}
	}
	ft_err(closedir(dir_cwd) == -1, t, __FILE__, __LINE__);
}

void	ft_get_cwd_names(char ***f_names, t_tr *t)
{
	int		names_num;
	char	**f_arr;

	ft_free_str(&t->f_cwd);
	t->f_cwd = getcwd(NULL, 0);
	names_num = ft_count_cwd_files_dir(t->f_cwd, t);
	f_arr = ft_calloc(sizeof(char *), names_num + 1);
	ft_err(!f_arr, t, __FILE__, __LINE__);
	f_arr[names_num] = NULL;
	ft_put_cwd_filename(names_num, f_arr, t->f_cwd, t);
	ft_free_str(&t->f_cwd);
	*f_names = f_arr;
}
