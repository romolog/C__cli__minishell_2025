/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_08_signals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:11:43 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:19:47 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// rl_on_new_line(); // Regenerate the prompt on a newline
// rl_replace_line("", 0); // Clear the previous text
static void	ft_sig_rline(int sig)
{
	extern sig_atomic_t		g_sig;
	int						errnum;	

	errnum = errno;
	g_sig = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	errno = errnum;
}

static void	ft_sig_catch(int sig)
{
	extern sig_atomic_t		g_sig;
	int						errnum;	

	if (!g_sig)
	{
		errnum = errno;
		g_sig = sig;
		if (sig == SIGQUIT)
			write (1, "Quit", 4);
		errno = errnum;
	}
}

void	ft_signal_handler_sigint_rline(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts;
	s->sa_handler = &ft_sig_rline;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGINT, s, NULL) == -1, t, __FILE__, __LINE__);
}

void	ft_signal_handler_sigint_main(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts;
	s->sa_handler = &ft_sig_catch;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGINT, s, NULL) == -1, t, __FILE__, __LINE__);
}

void	ft_signal_handler_sigquit_main(t_tr *t)
{
	t_sa	*s;

	s = t->sigacts + 1;
	s->sa_handler = &ft_sig_catch;
	s->sa_flags = SA_RESTART;
	ft_signal_mask_not_exit(s, t);
	ft_err(sigaction(SIGQUIT, s, NULL) == -1, t, __FILE__, __LINE__);
}
