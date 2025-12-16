/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:29:47 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 14:26:18 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_get_flags(t_s_printfmt *print)
{
	while (*(print->fmt) == '-' || *(print->fmt) == '0'\
			|| *(print->fmt) == '#' || *(print->fmt) == ' '\
			|| *(print->fmt) == '+')
	{
		if (*(print->fmt) == '-')
			print->flag_left = 1;
		else if (*(print->fmt) == '0')
			print->flag_0[0] = '0';
		else if (*(print->fmt) == '#')
			print->flag_sharp = 1;
		else if (*(print->fmt) == ' ')
			print->flag_spc = 1;
		else if (*(print->fmt) == '+')
			print->flag_sign = 1;
		(print->fmt)++;
	}
}

static void	ft_get_width(t_s_printfmt *print)
{
	while (*(print->fmt) >= '0' && *(print->fmt) <= '9')
	{
		print->width = (print->width) * 10 + (*(print->fmt) - '0');
		(print->fmt)++;
	}
}

static void	ft_get_precision(t_s_printfmt *print)
{
	if (*(print->fmt) == '.')
		(print->fmt)++;
	else
		return ;
	print->prcsn = 0;
	while (*(print->fmt) >= '0' && *(print->fmt) <= '9')
	{
		print->prcsn = (print->prcsn) * 10 + (*(print->fmt) - '0');
		(print->fmt)++;
	}
}

static int	ft_get_conversion(t_s_printfmt *print)
{
	char	*type_set;

	type_set = "cspdiuxX";
	if (*(print->fmt) == '%')
	{
		write(1, "%", 1);
		print->res++;
		ft_reset_print(print);
		return (2);
	}
	while (*type_set)
	{
		if (*type_set == *(print->fmt))
		{
			print->cnv = (*type_set);
			print->ph = 1;
			return (1);
		}
		type_set++;
	}
	print->fmt = NULL;
	print->res = -1;
	return (0);
}

int	ft_f(t_s_printfmt *print)
{
	if (*(print->fmt + 1) == '%')
		return (0);
	(print->fmt)++;
	ft_get_flags(print);
	ft_get_width(print);
	ft_get_precision(print);
	if (!ft_get_conversion(print))
		return (0);
	print->fmt++;
	return (1);
}
