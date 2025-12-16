/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_13_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:47 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/07 21:03:03 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_get_user(t_tr *t)
{
	char	*s;
	char	**e;
	size_t	i;

	ft_exec(&e, "id", t);
	s = e[0];
	while (s && *s && *s != '(')
		s++;
	s += (s && *s);
	i = 0;
	while (s && s[i] && s[i] != ' ' && (s[i] < 9 || s[i] > 13))
		i++;
	ft_add_str_malloc(&t->f_prompt, s, i - 1, t);
	ft_add_str_malloc(&t->f_prompt, "@", 1, t);
	if (s && *s)
		ft_add_str_malloc(&t->f_user, s, i - 1, t);
	ft_free_2d_char(&e);
	if (!t->f_user || !*t->f_user)
	{
		t->err = t->err_list->empty_user;
		ft_ctx(1, t, __FILE__, __LINE__);
	}
}

static int	ft_get_hostname_str(char **f_str, t_tr *t)
{
	int		fd;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	ft_ctx(fd < 0, t, __FILE__, __LINE__);
	if (fd < 0)
		return (0);
	*f_str = ft_get_next_line(fd);
	ft_err(close(fd) == -1, t, __FILE__, __LINE__);
	if (!f_str || !*f_str || !**f_str)
	{
		ft_free_str(f_str);
		return (0);
	}
	return (1);
}

static void	ft_get_hostname(t_tr *t)
{
	char	*f_str;
	char	*ptr;

	if (!ft_get_hostname_str(&f_str, t))
		return ;
	ptr = ft_strchr(f_str, '.');
	if (ptr)
		ft_add_str_malloc(&t->f_host, f_str, ptr - f_str, t);
	else
		ft_add_str_malloc(&t->f_host, f_str, ft_strlen(f_str), t);
	if (t->f_host && *t->f_host)
		ft_add_str_malloc(&t->f_prompt, t->f_host, ft_strlen(t->f_host), t);
	else
	{
		t->err = t->err_list->empty_host;
		ft_ctx(1, t, __FILE__, __LINE__);
	}
	ft_add_str_malloc(&t->f_prompt, ":", 1, t);
	ft_free_str(&f_str);
}

void	ft_set_tracker_prompt(t_tr *t)
{
	char	*label;

	label = "\033[0;36mMINISHELL R&I \033[1;96m";
	ft_add_str_malloc(&t->f_prompt, label, ft_strlen(label), t);
	ft_get_user(t);
	ft_get_hostname(t);
	ft_update_prompt_pwd(t);
	if (!t->f_prompt || ft_strlen(t->f_prompt) <= 2)
	{
		t->err = t->err_list->empty_prompt;
		ft_err(1, t, __FILE__, __LINE__);
	}
}
