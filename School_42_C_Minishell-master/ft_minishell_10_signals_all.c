/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_10_signals_all.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:11:43 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:19:56 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_signal_all_ignore(t_tr *t)
{
	ft_signal_handler_sigint_ignr(t);
	ft_signal_handler_sigquit_ignr(t);
}

static void	ft_sig_heredoc(int sig)
{
	write(1, "\n", 1);
	exit(sig);
}

void	ft_signal_handler_sigint_heredoc(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts;
	s->sa_handler = &ft_sig_heredoc;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGINT, s, NULL) == -1, t, __FILE__, __LINE__);
}
