/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_14_prompt_update.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:47 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:20:19 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_get_cwd(t_tr *t)
{
	char	*f_cd;
	char	*f_home_dir;
	char	*ptr;

	ft_free_str(&t->f_cwd);
	f_cd = getcwd(NULL, 0);
	f_home_dir = NULL;
	ft_getenv(&f_home_dir, "HOME", t);
	if (f_cd && f_home_dir \
		&& !ft_strncmp(f_cd, f_home_dir, ft_strlen(f_home_dir)))
	{
		ptr = f_cd + ft_strlen(f_home_dir);
		ft_add_str_malloc(&t->f_cwd, "~", 1, t);
	}
	else
		ptr = f_cd;
	ft_add_str_malloc(&t->f_cwd, ptr, ft_strlen(ptr), t);
	ft_free_str(&f_cd);
	ft_free_str(&f_home_dir);
}

void	ft_update_prompt_pwd(t_tr *t)
{
	char	*f_new_prompt;
	char	*ptr;

	f_new_prompt = NULL;
	ft_get_cwd(t);
	ptr = t->f_prompt;
	while (ptr && *ptr && *ptr != ':')
		ptr++;
	ft_add_str_malloc(&f_new_prompt, t->f_prompt, (ptr - t->f_prompt + 1), t);
	ft_add_str_malloc(&f_new_prompt, t->f_cwd, ft_strlen(t->f_cwd), t);
	ft_add_str_malloc(&f_new_prompt, "$\033[0m ", 6, t);
	ft_free_str(&t->f_cwd);
	ft_free_str(&t->f_prompt);
	t->f_prompt = f_new_prompt;
}
