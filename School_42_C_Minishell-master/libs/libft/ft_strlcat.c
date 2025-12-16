/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:12:51 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/26 17:48:53 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_s;
	size_t	len_d;
	size_t	i;

	len_s = ft_strlen(src);
	len_d = ft_strlen(dst);
	if ((dst == NULL || src == NULL))
		return (0);
	else if (len_d >= size)
		return (size + len_s);
	i = 0;
	while (src[i] && len_d + i < size - 1)
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}
