/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:46:02 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/28 13:21:55 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			k = 0;
			while (i + k < len && big[i + k] == little[k] && big[i + k])
				k++;
			if (i + k == len && little[k] != '\0')
				return (NULL);
			else if (i + k == len && little[k] == '\0')
				return ((char *)(big + i));
			else if (i + k < len && little[k] == '\0')
				return ((char *)(big + i));
			else if (i + k < len && big[i + k] == '\0')
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
