/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:46:51 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/26 15:42:00 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	d = (char *)dest;
	s = (char *)src;
	if (d - s == 0 || n == 0)
		return (dest);
	else if (d - s > 0)
	{
		while (n--)
			d[n] = s[n];
		return (dest);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
		return (dest);
	}
}

// static void	ft_cpy(char *dest, char *src, size_t n)
// {
// 	size_t	i;
//
// 	i = 0;
// 	while (i < n)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// }
// void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	char	*d;
// 	char	*s;
// 	char	*buf;
//
// 	d = (char *)dest;
// 	s = (char *)src;
// 	buf = malloc(n);
// 	if (buf == NULL)
// 		return (NULL);
// 	else
// 	{
// 		ft_cpy(buf, s, n);
// 		ft_cpy(d, buf, n);
// 		free(buf);
// 	}
// 	return (dest);
// }