/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:52:36 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/01 12:13:33 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;
	size_t	size;

	s_len = ft_strlen(s);
	if (start >= s_len)
		size = 1;
	else if (s_len - start < len)
		size = s_len - start + 1;
	else
		size = len + 1;
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (size > 1 && i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// if (start >= s_len)
// 	return (NULL);
// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "1234";
// 	size_t len = 40;
// 	unsigned int start = 0;
// 	printf(">>%s<<\n", ft_substr(str, start, len));
// 	return (0);
// }