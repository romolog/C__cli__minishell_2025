/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_numlen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:19:39 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/08 18:17:31 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reset_print(t_s_printfmt *print)
{
	print->ph = 0;
	print->flag_left = 0;
	print->flag_sign = 0;
	print->flag_sharp = 0;
	print->flag_spc = 0;
	print->flag_0[0] = ' ';
	print->width = 0;
	print->prcsn = -1;
	print->cnv = 0;
}

int	ft_num_len_base(long long num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len++;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

int	ft_llu_len_base(unsigned long long num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

int	ft_u_len_base(unsigned int num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}
