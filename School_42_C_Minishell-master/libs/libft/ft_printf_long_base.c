/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_long_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:16:11 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 18:40:27 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_zeroprefix(t_s_printfmt *p, int len, long long num)
{
	while ((p->prcsn - len) > 0)
	{
		write(1, "0", 1);
		len++;
	}
	if (num >= 0 && p->flag_sign)
		len++;
	while ((p->width - len) > 0 && p->flag_0[0] == '0' && p->prcsn == -1)
	{
		write(1, "0", 1);
		len++;
	}
}

static void	ft_put_prefix(long long *num, t_s_printfmt *p, int len)
{
	long long	n;

	n = *num;
	if (n < 0)
	{
		(*num) *= -1;
		write(1, "-", 1);
		len--;
		if (p->width)
			p->width--;
	}
	if (n >= 0 && p->flag_sign)
		write(1, "+", 1);
	else if (n >= 0 && p->flag_spc)
	{
		write(1, " ", 1);
		p->width--;
	}
	ft_put_zeroprefix(p, len, n);
}

static void	ft_put_dgtbase(long long num, t_s_printfmt *p, int len)
{
	char		*radix_low;
	char		*radix_up;

	radix_low = "0123456789abcdef";
	radix_up = "0123456789ABCDEF";
	ft_put_prefix(&num, p, len);
	if (p->prcsn == 0 && num == 0)
		return ;
	else if (p->cnv == 'X')
		write(1, radix_up + num, 1);
	else
		write(1, radix_low + num, 1);
}

void	ft_print_long_base(long long num, int base, t_s_printfmt *p, int len)
{
	char		*radix_low;
	char		*radix_up;

	radix_low = "0123456789abcdef";
	radix_up = "0123456789ABCDEF";
	if (num < (base - 1) * -1 || num > (base - 1))
	{
		ft_print_long_base(num / base, base, p, len);
		if (p->cnv == 'X' && (num % base) >= 0)
			write(1, radix_up + (num % base), 1);
		else if (p->cnv == 'X' && (num % base) < 0)
			write(1, radix_up - (num % base), 1);
		else if ((num % base) >= 0)
			write(1, radix_low + (num % base), 1);
		else
			write(1, radix_low - (num % base), 1);
	}
	else
		ft_put_dgtbase(num, p, len);
}
