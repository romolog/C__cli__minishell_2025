/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:06:15 by rponomar          #+#    #+#             */
/*   Updated: 2025/01/23 13:19:10 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*ptr_populate;
	char	n;
	size_t	len;

	n = 0;
	if (size)
	{
		if (nmemb != nmemb * size / size)
			return (NULL);
	}
	len = nmemb * size;
	ptr = malloc(nmemb * size);
	if (len && ptr)
	{
		ptr_populate = (char *)ptr;
		while (len--)
			ptr_populate[len] = n;
	}
	return (ptr);
}

// write(2, "Error: size_t overflow\n", 23);
// static size_t	ft_max_size_t(void)
// {
// 	size_t	res;
// 	size_t	k;

// 	res = 1;
// 	k = 0;
// 	while (k < res)
// 	{
// 		k = res;
// 		res = (res << 1) + 1;
// 	}
// 	return (res);
// }
