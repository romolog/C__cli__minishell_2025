/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:17:14 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/30 16:17:27 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(src);
	if (size == 0)
		return (len_s);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_s);
}

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	len_s;
// 	size_t	i;
//
// 	if (dst == NULL || src == NULL)
// 		return (0);
// 	len_s = ft_strlen(src);
// 	if (size == 0)
// 		return (len_s);
// 	i = 0;
// 	while (src[i] && i < size - 1)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (len_s);
// }