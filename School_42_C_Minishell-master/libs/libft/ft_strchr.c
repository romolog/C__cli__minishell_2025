/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:02:05 by rponomar          #+#    #+#             */
/*   Updated: 2025/01/07 18:58:10 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		target;

	ptr = (char *)s;
	target = c << ((sizeof(int) - 1) * 8);
	target = target >> ((sizeof(int) - 1) * 8);
	while (*ptr || *ptr == target)
	{
		if (*ptr == target)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

//	str = "ababa"
//	ptr = ft_strrchr(str, 'b');
//	ptr - str = 4;
//	ptr = ft_strchr(str, 'b');
//	ptr - str = 1;
//	
//	str = "aaa";
//	ptr = ft_strrchr(str, 'b');
//	ptr == NULL;

// char	*ft_strchr(const char *s, int c)
// {
// 	char	*ptr;

// 	ptr = (char *)s;
// 	if (s == NULL || c < 0 || c > 127)
// 		return (NULL);
// 	while (*ptr || *ptr == c)
// 	{
// 		if (*ptr == c)
// 			return (ptr);
// 		ptr++;
// 	}
// 	return (NULL);
// }
// #include <stdio.h>
// #include <string.h>
// int main()
// {	
// 	char str[] = {'a', (char)('2' - 256)};
// 	int	t = '2' - 256;
// 	printf("\n%p : %p\n", strchr(str, t), ft_strchr(str, t));
// }