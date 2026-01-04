/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_11_signals_exit_status.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:11:43 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:20:00 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_sig_exit_status(t_tr *t)
{
	extern sig_atomic_t		g_sig;
	char					*f_str;

	if (!g_sig)
		return (0);
	t->exit_status = (int)(g_sig + 128);
	f_str = ft_itoa(t->exit_status);
	ft_strlcpy(t->exit_les, f_str, ft_strlen(f_str) + 1);
	ft_free_str(&f_str);
	return (1);
}
