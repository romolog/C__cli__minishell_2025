/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:02:17 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/27 18:20:47 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*t;
	char	*p;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	t = (char *)dest;
	p = (char *)src;
	i = 0;
	while (i < n)
	{
		t[i] = p[i];
		i++;
	}
	return (dest);
}
