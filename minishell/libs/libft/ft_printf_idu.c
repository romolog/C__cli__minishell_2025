/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_idu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 20:05:36 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 19:40:52 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_set_ls(long long num, t_s_printfmt *p, int *len, int *space)
{
	*len = ft_num_len_base(num, 10);
	if (p->prcsn > *len || (!num && !p->prcsn))
		*len = p->prcsn;
	if (num < 0 && p->prcsn >= *len)
		(*len)++;
	if (num >= 0 && (p->flag_sign || p->flag_spc))
		(*len)++;
	if ((p->width > (*len)) && ((p->flag_0[0]) == ' ' || p->prcsn >= 0))
		*space = (p->width) - (*len);
	if ((*len) && p->width \
		&& !num && !p->prcsn && !p->flag_spc && !p->flag_sign)
		*space += 1;
	if (p->width > (*len))
		p->res += p->width;
	else
		p->res += (*len);
}

void	ft_print_idu(long long num, t_s_printfmt *print)
{
	int	len;
	int	fill_space;

	len = 0;
	fill_space = 0;
	ft_set_ls(num, print, &len, &fill_space);
	if (print->flag_left)
	{
		ft_print_long_base(num, 10, print, ft_num_len_base(num, 10));
		while (fill_space--)
			write(1, " ", 1);
	}
	else
	{
		while (fill_space--)
			write(1, " ", 1);
		ft_print_long_base(num, 10, print, ft_num_len_base(num, 10));
	}
	ft_reset_print(print);
}
