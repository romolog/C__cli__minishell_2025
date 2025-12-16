/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:31:26 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/07 20:49:08 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(char character, t_s_printfmt *print)
{
	int		i;

	i = -1;
	if (print->flag_left == 0)
	{
		while (++i < print->width - 1)
			write(1, " ", 1);
		write(1, &character, 1);
	}
	else
	{
		write(1, &character, 1);
		while (++i < print->width - 1)
			write(1, " ", 1);
	}
	if (print->width > 1)
		print->res += (print->width - 1);
	print->res++;
	ft_reset_print(print);
}
