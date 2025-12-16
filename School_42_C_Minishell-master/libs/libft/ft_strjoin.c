/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:09:22 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/28 18:06:28 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_max_int(void)
{
	int	res;
	int	k;

	res = 1;
	k = 0;
	while (k < res)
	{
		k = res;
		if (((res << 1) + 1) > 0)
			res = (res << 1) + 1;
	}
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len;
	size_t	i;
	size_t	k;	

	len = ft_strlen(s1);
	if (len <= ft_max_int() - ft_strlen(s2) - 1)
		len += ft_strlen(s2);
	else
		return (NULL);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	k = 0;
	while (i < len && s2[k])
		ptr[i++] = s2[k++];
	ptr[i] = '\0';
	return (ptr);
}

// static size_t	ft_max_size_t(void)
// {
// 	size_t	res;
// 	size_t	k;
//
// 	res = 1;
// 	k = 0;
// 	while (k < res)
// 	{
// 		k = res;
// 		if (((res << 1) + 1) > 0)
// 			res = (res << 1) + 1;
// 	}
// 	return (res);
// }