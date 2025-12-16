/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_12_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:34:24 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/07 19:43:31 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_set_tracker_start_path(t_tr *t)
{
	char	*f_str;
	int		fd;

	fd = open("/etc/environment", O_RDONLY);
	ft_ctx(fd < 0, t, __FILE__, __LINE__);
	if (fd < 0)
		return ;
	f_str = ft_get_next_line(fd);
	ft_err(close(fd) == -1, t, __FILE__, __LINE__);
	if (f_str && ft_strlen(f_str) >= 6)
		ft_add_str_malloc(&t->f_path_start, f_str + 6, \
							ft_strlen(f_str + 6) - 2, t);
	if (f_str && *f_str)
		ft_add_str_malloc(&t->f_path_start, ":", 1, t);
	ft_free_str(&f_str);
	ft_getenv(&f_str, "PATH", t);
	if (f_str)
		ft_add_str_malloc(&t->f_path_start, f_str, ft_strlen(f_str), t);
	if (!t->f_path_start || !*t->f_path_start)
	{
		t->err = t->err_list->empty_env_path;
		ft_e(1, NULL, NULL, t);
	}
	ft_free_str(&f_str);
}
