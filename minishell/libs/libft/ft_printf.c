/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:22:57 by rponomar          #+#    #+#             */
/*   Updated: 2024/10/29 21:02:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_letter(t_s_printfmt *print)
{
	while (*(print->fmt) == '%' && *(print->fmt + 1) == '%')
	{
		write(1, print->fmt, 1);
		print->fmt += 2;
		print->res += 1;
	}
	if (*(print->fmt) == '%')
	{
		return ;
	}
	else if (!*(print->fmt))
		return ;
	while (*(print->fmt) && *(print->fmt) != '%')
	{
		write(1, print->fmt++, 1);
		print->res++;
	}
}

static void	ft_set_p(t_s_printfmt *print, char *fmt)
{
	print->fmt = fmt;
	print->ph = 0;
	print->res = 0;
	print->flag_left = 0;
	print->flag_sign = 0;
	print->flag_sharp = 0;
	print->flag_spc = 0;
	print->flag_0[0] = ' ';
	print->width = 0;
	print->prcsn = -1;
	print->cnv = 0;
}

int	ft_printf(const char *format_str, ...)
{
	t_s_printfmt	p;

	ft_set_p(&p, (char *)format_str);
	va_start(p.arg_ptr, format_str);
	while (p.fmt && *p.fmt)
	{
		if (*p.fmt == '%' && ft_f(&p) && p.cnv == 'c')
			ft_print_char(va_arg(p.arg_ptr, int), &p);
		else if (p.ph && p.cnv == 's')
			ft_print_str(va_arg(p.arg_ptr, char *), &p);
		else if (p.ph && p.cnv == 'p')
			ft_print_ptr(va_arg(p.arg_ptr, unsigned long), &p);
		else if (p.ph && (p.cnv == 'd' || p.cnv == 'i'))
			ft_print_idu(va_arg(p.arg_ptr, int), &p);
		else if (p.ph && (p.cnv == 'u'))
			ft_print_idu(va_arg(p.arg_ptr, unsigned int), &p);
		else if (p.ph && (p.cnv == 'x'))
			ft_print_xd(va_arg(p.arg_ptr, unsigned int), &p);
		else if (p.ph && (p.cnv == 'X'))
			ft_print_xd(va_arg(p.arg_ptr, unsigned int), &p);
		else if (p.fmt)
			ft_print_letter(&p);
	}
	va_end(p.arg_ptr);
	return (p.res);
}

// pritnf("%[flags][width][.precision][size][specifier]", var);
// 
//www.ibm.com/docs/en/i/7.4?topic=functions-printf-print-formatted-characters