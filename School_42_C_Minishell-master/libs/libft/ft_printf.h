/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:25:11 by rponomar          #+#    #+#             */
/*   Updated: 2024/09/09 18:18:06 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef unsigned long long	t_llu;
typedef struct s_printfmt
{
	va_list			arg_ptr;
	char			*fmt;
	int				ph;
	int				res;
	char			flag_left;
	char			flag_sign;
	char			flag_sharp;
	char			flag_spc;
	char			flag_0[1];
	int				width;
	int				prcsn;
	char			cnv;
}	t_s_printfmt;

int		ft_printf(const char *fmt, ...);
int		ft_f(t_s_printfmt *print);
void	ft_reset_print(t_s_printfmt *print);
void	ft_print_char(char character, t_s_printfmt *print);
void	ft_print_str(char *str, t_s_printfmt *print);
void	ft_print_long_base(long long n, int base, t_s_printfmt *p, int len);
void	ft_print_llu_base(t_llu n, int base, t_s_printfmt *p, int len);
int		ft_num_len_base(long long num, int base);
int		ft_llu_len_base(unsigned long long num, int base);
int		ft_u_len_base(unsigned int num, int base);
void	ft_print_ptr(unsigned long ptr, t_s_printfmt *print);
void	ft_print_idu(long long num, t_s_printfmt *print);
void	ft_print_xd(unsigned int xd, t_s_printfmt *print);

#endif
