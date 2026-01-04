/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_01_signals_start.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:24:18 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:19:02 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_set_sigation_ignore(int sig, t_sa *s, char *prog_name, t_tr *t)
{
	s->sa_handler = SIG_IGN;
	s->sa_flags = SA_RESTART;
	ft_err_start(sigemptyset(&s->sa_mask) == -1, prog_name, t);
	ft_err_start(sigaddset(&s->sa_mask, SIGQUIT) == -1, prog_name, t);
	ft_err_start(sigaddset(&s->sa_mask, SIGINT) == -1, prog_name, t);
	ft_err_start(sigaction(sig, s, NULL) == -1, prog_name, t);
}

void	ft_signal_all_ignore_start(char *prog_name, t_tr *t)
{
	t_sa	*s;

	s = t->sigacts;
	ft_set_sigation_ignore(SIGINT, s, prog_name, t);
	s = t->sigacts + 1;
	ft_set_sigation_ignore(SIGQUIT, s, prog_name, t);
}
