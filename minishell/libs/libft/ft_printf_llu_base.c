/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_llu_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:16:11 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 19:57:00 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_zeroprefix(t_s_printfmt *p, int len, t_llu num)
{
	while (p->cnv != 'p' && (p->prcsn - len) > 0)
	{
		write(1, "0", 1);
		len++;
	}
	if (p->flag_sharp && num)
		len += 2;
	while (p->cnv != 'p' && (p->width - len) > 0 \
			&& p->flag_0[0] == '0' && p->prcsn == -1)
	{
		write(1, "0", 1);
		len++;
	}
}

static void	ft_put_prefix(t_s_printfmt *p, int len, t_llu num)
{
	if (p->cnv != 'p' && p->flag_spc)
	{
		write(1, " ", 1);
		p->width--;
	}
	ft_put_zeroprefix(p, len, num);
}

static void	ft_put_dgtbase(t_llu num, t_s_printfmt *p, int len)
{
	char		*radix_low;
	char		*radix_up;

	radix_low = "0123456789abcdef";
	radix_up = "0123456789ABCDEF";
	ft_put_prefix(p, len, num);
	if (p->prcsn == 0 && num == 0)
		return ;
	else if (p->cnv == 'X')
		write(1, radix_up + num, 1);
	else
		write(1, radix_low + num, 1);
}

void	ft_print_llu_base(t_llu num, int base, t_s_printfmt *p, int len)
{
	char		*radix_low;
	char		*radix_up;

	radix_low = "0123456789abcdef";
	radix_up = "0123456789ABCDEF";
	if (num > (t_llu)(base - 1))
	{
		ft_print_llu_base(num / base, base, p, len);
		if (p->cnv == 'X' && (num % base) >= 0)
			write(1, radix_up + (num % base), 1);
		else
			write(1, radix_low + (num % base), 1);
	}
	else
		ft_put_dgtbase(num, p, len);
}
