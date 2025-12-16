/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_62_utils_free.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:58:07 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:11 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_free_2d_char(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = -1;
	while ((*arr)[++i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
	}
	free(*arr);
	*arr = NULL;
}

void	ft_free_str(char **str)
{
	if (str && *str)
		free(*str);
	if (str)
		*str = NULL;
}

void	ft_free_int(int **ptr)
{
	if (ptr && *ptr)
		free(*ptr);
	if (ptr)
		*ptr = NULL;
}

void	ft_free_2d_int(int ***arr)
{
	size_t	i;

	if (!arr || !*arr || !**arr)
		return ;
	i = -1;
	while ((*arr)[++i])
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	ft_free_close_fd(int *fd, t_tr *t)
{
	if (*fd < 0)
		return ;
	ft_err(close(*fd), t, __FILE__, __LINE__);
	*fd = -1;
}
