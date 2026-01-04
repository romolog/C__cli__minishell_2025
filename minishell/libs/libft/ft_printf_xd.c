/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:11:57 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 19:52:53 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_ptr(unsigned int xd, t_s_printfmt *print)
{
	int	base;

	base = 16;
	if (print->cnv == 'x' && print->flag_sharp && xd)
		write(1, "0x", 2);
	if (print->cnv == 'X' && print->flag_sharp && xd)
		write(1, "0X", 2);
	ft_print_llu_base(xd, base, print, ft_u_len_base(xd, 16));
}

static void	ft_set_ls(unsigned int xd, t_s_printfmt *p, int *len, int *space)
{
	*len = ft_u_len_base(xd, 16);
	if (p->prcsn > *len || (!xd && !p->prcsn))
		*len = p->prcsn;
	if (p->flag_sharp && xd)
		(*len) += 2;
	if ((p->width > (*len)) && ((p->flag_0[0]) == ' ' || p->prcsn >= 0))
		*space = (p->width) - (*len);
	if ((*len) && p->width && !xd && !p->prcsn && !p->flag_spc && !p->flag_sign)
		*space += 1;
	if (p->width > (*len))
		p->res += p->width;
	else
		p->res += (*len);
}

void	ft_print_xd(unsigned int xd, t_s_printfmt *print)
{
	int	len;
	int	fill_space;

	len = 0;
	fill_space = 0;
	ft_set_ls(xd, print, &len, &fill_space);
	if (print->flag_left)
	{
		ft_put_ptr(xd, print);
		while (fill_space--)
			write(1, " ", 1);
	}
	else
	{
		while (fill_space--)
			write(1, " ", 1);
		ft_put_ptr(xd, print);
	}
	ft_reset_print(print);
}
