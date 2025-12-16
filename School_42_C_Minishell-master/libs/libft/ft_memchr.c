/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:19:05 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/28 11:54:07 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	target;
	size_t			i;

	ptr = (unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n && ptr[i] != target)
		i++;
	if (i < n)
		return ((void *)(ptr + i));
	return (NULL);
}
