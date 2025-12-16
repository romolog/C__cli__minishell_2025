/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:31:52 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/31 16:22:08 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_int_len(int num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len++;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		num;

	num = n;
	len = ft_int_len(n);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		if ((num % 10) > 0)
			str[len] = '0' + (num % 10);
		else
			str[len] = '0' - (num % 10);
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", ft_itoa(-123));
// 	return (0);
// }