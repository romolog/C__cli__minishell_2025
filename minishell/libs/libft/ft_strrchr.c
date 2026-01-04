/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:17:45 by rponomar          #+#    #+#             */
/*   Updated: 2025/01/07 18:56:32 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		target;

	target = c << ((sizeof(int) - 1) * 8);
	target = target >> ((sizeof(int) - 1) * 8);
	ptr = (char *)s;
	while (*ptr)
		ptr++;
	if (*ptr == target)
		return (ptr);
	if (ptr - s > 0)
		ptr--;
	while (ptr - s >= 0)
	{
		if (*ptr == target)
			return (ptr);
		ptr--;
	}
	return (NULL);
}

//	str = "ababa"
//	ptr = ft_strrchr(str, 'b');
//	ptr - str = 4;
//	ptr = ft_strchr(str, 'b');
//	ptr - str = 1;

// char	*ft_strrchr(const char *s, int c)
// {
// 	char	*ptr;
//
// 	if (s == NULL || c < 0 || c > 127)
// 		return (NULL);
// 	ptr = (char *)s;
// 	while (*ptr)
// 		ptr++;
// 	if (*ptr == c)
// 		return (ptr);
// 	if (ptr - s > 0)
// 		ptr--;
// 	while (ptr - s >= 0)
// 	{
// 		if (*ptr == c)
// 			return (ptr);
// 		ptr--;
// 	}
// 	return (NULL);
// }