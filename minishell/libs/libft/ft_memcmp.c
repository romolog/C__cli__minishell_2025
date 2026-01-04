/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:00:19 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/28 11:18:16 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str_1;
	unsigned char	*str_2;

	str_1 = (unsigned char *)s1;
	str_2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && str_1[i] == str_2[i])
		i++;
	if (i == n && n > 0)
		return (str_1[i - 1] - str_2[i - 1]);
	return (str_1[i] - str_2[i]);
}
