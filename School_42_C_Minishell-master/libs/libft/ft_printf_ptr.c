/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:23:57 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 19:56:48 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_ptr(unsigned long ptr, t_s_printfmt *print)
{
	int	base;

	base = 16;
	if (!ptr)
		write(1, "(nil)", 5);
	else
	{
		write(1, "0x", 2);
		ft_print_llu_base(ptr, base, print, ft_llu_len_base(ptr, 16));
	}
}

static void	ft_set_ls(unsigned long ptr, t_s_printfmt *p, int *len, int *space)
{
	*len = ft_llu_len_base(ptr, 16) + 2;
	if (!ptr)
		*len = 5;
	if (p->width > *len)
		*space = (p->width) - *len;
	if (p->width > (*len))
		p->res += p->width;
	else
		p->res += (*len);
}

void	ft_print_ptr(unsigned long ptr, t_s_printfmt *print)
{
	int	len;
	int	fill_space;

	len = 0;
	fill_space = 0;
	ft_set_ls(ptr, print, &len, &fill_space);
	if (print->flag_left)
	{
		ft_put_ptr(ptr, print);
		while (fill_space--)
			write(1, " ", 1);
	}
	else
	{
		while (fill_space--)
			write(1, " ", 1);
		ft_put_ptr(ptr, print);
	}
	ft_reset_print(print);
}
