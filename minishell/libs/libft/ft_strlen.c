/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:47:28 by rponomar          #+#    #+#             */
/*   Updated: 2024/11/23 14:51:01 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_max_size_t(void)
{
	size_t	res;
	size_t	k;

	res = 1;
	k = 0;
	while (k < res)
	{
		k = res;
		res = (res << 1) + 1;
	}
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	size_t	max_len;

	i = 0;
	max_len = ft_max_size_t();
	while (i < max_len && s[i])
		i++;
	return (i);
}

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;
//
// 	i = 0;
// 	if (s == NULL)
// 		return (0);
// 	while (s[i] && i < ft_max_size_t() - 1)
// 		i++;
// 	return (i);
// }