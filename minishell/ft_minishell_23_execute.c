/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_23_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:50:04 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:30:39 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_skip_part(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;

	tkn = *ptr_tkn;
	tkn = tkn->next;
	while (tkn && !((tkn->ao_and || tkn->ao_or \
		|| tkn->brace_close) && tkn->enclsr == encl))
		tkn = tkn->next;
	if (tkn && tkn->brace_close && tkn->enclsr == encl)
	{
		t->do_exit = 1;
		t->exit_status = ft_atoi(t->exit_les);
		ft_free_all(t);
	}
	*ptr_tkn = tkn;
}

static void	ft_execute_part(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	t_tkn	*tkn;

	tkn = *ptr_tkn;
	tkn = tkn->next;
	ft_execute_pipe(encl, &tkn, t);
	if (tkn && tkn->brace_close && tkn->enclsr == encl)
	{
		t->do_exit = 1;
		t->exit_status = ft_atoi(t->exit_les);
		ft_free_all(t);
	}
	*ptr_tkn = tkn;
}

static void	ft_execute_andor(int encl, t_tkn **ptr_tkn, t_tr *t)
{
	extern sig_atomic_t		g_sig;
	t_tkn					*tkn;

	if (!t->tkn_head || !ptr_tkn || !*ptr_tkn)
		return ;
	tkn = *ptr_tkn;
	if (g_sig \
		&& (tkn && (tkn->ao_and || tkn->ao_or) && tkn->enclsr == encl))
	{
		ft_sig_exit_status(t);
		t->do_exit = !t->pid_current;
		ft_free_all(t);
		*ptr_tkn = NULL;
		return ;
	}
	else if (tkn && (tkn->ao_and || tkn->ao_or) && tkn->enclsr == encl)
	{
		if ((tkn->ao_and && ft_strncmp(t->exit_les, "0", 2)) \
			|| (tkn->ao_or && !ft_strncmp(t->exit_les, "0", 2)))
			ft_skip_part(encl, &tkn, t);
		else
			ft_execute_part(encl, &tkn, t);
	}
	*ptr_tkn = tkn;
}

void	ft_execute(int encl, t_tkn *tkn, t_tr *t)
{
	extern sig_atomic_t		g_sig;

	if (!tkn || g_sig)
		return ;
	ft_signal_handler_sigint_main(t);
	ft_signal_handler_sigquit_main(t);
	while (!g_sig && t->tkn_head \
		&& tkn && !(tkn->brace_close && tkn->enclsr == encl))
	{
		ft_execute_pipe(encl, &tkn, t);
		ft_execute_andor(encl, &tkn, t);
	}
	if (g_sig)
		return ;
	if (t->tkn_head && tkn && tkn->brace_close && tkn->enclsr == encl)
	{
		t->do_exit = 1;
		t->exit_status = ft_atoi(t->exit_les);
		ft_free_all(t);
	}
}
