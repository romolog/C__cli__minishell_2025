/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:17:07 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 19:56:40 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen_trunc(char *str, int trunc, t_s_printfmt *print)
{
	int	len;

	len = 0;
	while (*str++ && print->res + len < __INT_MAX__)
		len++;
	if (print->res + len == __INT_MAX__ && *str && trunc == -1)
		return (-1);
	if (len <= trunc || trunc == -1)
		return (len);
	else
		return (trunc);
}

static int	ft_set_len_space(char *str, t_s_printfmt *p, int *len, int *space)
{
	*len = ft_strlen_trunc(str, p->prcsn, p);
	if (*len != -1)
	{
		if (p->width > *len)
			*space = (p->width) - *len;
		if (p->width > (*len))
			p->res += p->width;
		else
			p->res += (*len);
		return (1);
	}
	else
	{
		ft_reset_print(p);
		p->res = -1;
		p->fmt = NULL;
		return (0);
	}
}

static int	ft_print_null_ptr(char *str, t_s_printfmt *p)
{
	int	fill_space;

	fill_space = (p->width) - 6 * (p->prcsn >= 6 || p->prcsn == -1);
	if (!str)
	{
		p->res += 6 * ((p->prcsn >= 6 || p->prcsn == -1) && (p->width <= 6));
		p->res += ((p->width > (6 * (p->prcsn >= 6 || p->prcsn == -1))) \
					* p->width);
		while (!p->flag_left && fill_space > 0)
		{
			write(1, " ", 1);
			fill_space--;
		}
		if (p->prcsn >= 6 || p->prcsn == -1)
			write(1, "(null)", 6);
		while (p->flag_left && fill_space > 0)
		{
			write(1, " ", 1);
			fill_space--;
		}
		ft_reset_print(p);
		return (1);
	}
	else
		return (0);
}

void	ft_print_str(char *str, t_s_printfmt *print)
{
	int	len;
	int	fill_space;

	len = 0;
	fill_space = 0;
	if (ft_print_null_ptr(str, print))
		return ;
	else if (!ft_set_len_space(str, print, &len, &fill_space))
		return ;
	if (print->flag_left)
	{
		while (len--)
			write(1, str++, 1);
		while (fill_space--)
			write(1, " ", 1);
	}
	else
	{
		while (fill_space--)
			write(1, " ", 1);
		while (len--)
			write(1, str++, 1);
	}
	ft_reset_print(print);
}
