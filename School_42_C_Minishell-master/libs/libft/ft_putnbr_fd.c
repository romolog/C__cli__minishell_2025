/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:29:49 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/31 18:38:38 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_int(int num, int fd)
{
	char	p;

	if (num < -9 || num > 9)
	{
		ft_print_int(num / 10, fd);
		if ((num % 10) > 0)
			p = '0' + (num % 10);
		else
			p = '0' - (num % 10);
		write (fd, &p, 1);
	}
	else
	{
		if (num < 0)
			write(fd, "-", 1);
		if ((num % 10) > 0)
			p = '0' + (num % 10);
		else
			p = '0' - (num % 10);
		write (fd, &p, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd >= 0)
	{
		ft_print_int(n, fd);
	}
}

// write(fd, "\0", 1);
// int	main(void)
// {
// 	ft_putnbr_fd(-123, 1);
// 	write(1, "\n", 1);
// 	return (0);
// }
