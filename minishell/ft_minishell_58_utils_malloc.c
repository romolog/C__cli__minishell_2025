/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_58_utils_malloc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:38:06 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/08 13:47:11 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_strlcpy_malloc(char *ptr, size_t ptr_len, t_tr *t)
{
	char	*f_str;

	if (!ptr)
		return (NULL);
	f_str = malloc(ptr_len + 1);
	ft_err(!f_str, t, __FILE__, __LINE__);
	if (!f_str)
		return (NULL);
	ft_strlcpy(f_str, ptr, ptr_len + 1);
	return (f_str);
}

static void	ft_call_copy(char *f_str, char **dst, char *add, int add_len)
{
	int		i;

	ft_strlcpy(f_str, *dst, ft_strlen(*dst) + 1);
	if (ft_strlen(add) >= (size_t)add_len)
		ft_strlcpy(f_str + ft_strlen(*dst), add, add_len + 1);
	else
	{
		ft_strlcpy(f_str + ft_strlen(*dst), add, ft_strlen(add) + 1);
		i = ft_strlen(*dst) + ft_strlen(add) - 1;
		while (++i <= add_len)
			f_str[i] = '\0';
	}
	free(*dst);
	*dst = f_str;
}

void	ft_add_str_malloc(char **dst, char *add, size_t add_len, t_tr *t)
{
	char	*f_str;

	if (!add || !dst)
		return ;
	if (!*dst)
	{
		*dst = ft_strlcpy_malloc(add, add_len, t);
		ft_err(!*dst, t, __FILE__, __LINE__);
		return ;
	}
	else if (!add_len || (ft_strlen(*dst) < ft_strlen(*dst) + add_len))
	{
		f_str = malloc(ft_strlen(*dst) + add_len + 1);
		ft_err(!f_str, t, __FILE__, __LINE__);
		if (!f_str)
			return ;
		ft_call_copy(f_str, dst, add, add_len);
		return ;
	}
	t->err = t->err_list->overflow;
	ft_err(1, t, __FILE__, __LINE__);
}

void	ft_trim_str_malloc(char **str, char ch, t_tr *t)
{
	char	*temp;
	size_t	i;

	if (!str || !*str || !**str || !ch)
		return ;
	i = 0;
	while ((*str)[i] && (*str)[i] != ch)
		i++;
	if (!*(str + i))
		return ;
	ft_add_str_malloc(&temp, *str, i + 1, t);
	ft_free_str(str);
	*str = temp;
}

void	ft_malloc_str(int conditon, char **str, int *memsize, t_tr *t)
{
	char	*s;

	if (!conditon)
		return ;
	if (*memsize == __INT_MAX__)
	{
		free(*str);
		t->err = t->err_list->overflow;
		ft_err(1, t, __FILE__, __LINE__);
	}
	else if ((*memsize) == ((*memsize) + 9 * (*memsize)) / 10)
		(*memsize) *= 10;
	else
		(*memsize) = __INT_MAX__;
	s = malloc(*memsize);
	if (!s)
		free(*str);
	ft_err((!s), t, __FILE__, __LINE__);
	if (*str)
	{
		ft_strlcpy(s, *str, ft_strlen(*str) + 1);
		free(*str);
	}
	*str = s;
}
