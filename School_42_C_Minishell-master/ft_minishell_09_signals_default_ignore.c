/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_09_signals_default_ignore.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:11:43 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:19:52 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_signal_mask_not_exit(t_sa *s, t_tr *t)
{
	ft_err(sigemptyset(&s->sa_mask) == -1, t, __FILE__, __LINE__);
	ft_err(sigaddset(&s->sa_mask, SIGQUIT) == -1, t, __FILE__, __LINE__);
	ft_err(sigaddset(&s->sa_mask, SIGINT) == -1, t, __FILE__, __LINE__);
}

void	ft_signal_handler_sigquit_ignr(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts + 1;
	s->sa_handler = SIG_IGN;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGQUIT, s, NULL) == -1, t, __FILE__, __LINE__);
}

void	ft_signal_handler_sigquit_dflt(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts + 1;
	s->sa_handler = SIG_DFL;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGQUIT, s, NULL) == -1, t, __FILE__, __LINE__);
}

void	ft_signal_handler_sigint_dflt(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts;
	s->sa_handler = SIG_DFL;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGINT, s, NULL) == -1, t, __FILE__, __LINE__);
}

void	ft_signal_handler_sigint_ignr(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts;
	s->sa_handler = SIG_IGN;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGINT, s, NULL) == -1, t, __FILE__, __LINE__);
}
