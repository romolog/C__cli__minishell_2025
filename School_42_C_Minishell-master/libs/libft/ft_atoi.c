/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:22:27 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/28 13:47:51 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int		res;
	int		minus;
	char	*ptr;

	res = 0;
	minus = 1;
	ptr = (char *)nptr;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\v'\
			|| *ptr == '\f' || *ptr == '\r' || *ptr == '\n')
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		minus *= (*ptr == '-') * -1 + (*ptr == '+');
		ptr++;
	}
	while (*ptr == '0')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
	{
		res = res * 10 + ((*ptr) - '0');
		ptr++;
	}
	return (res * minus);
}
