/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_00_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:42:55 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 14:34:12 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

sig_atomic_t	g_sig;

static void	ft_null_line(t_tr *t)
{
	if (t->f_line)
		return ;
	write(1, "exit\n", 5);
	t->exit_status = 0;
	t->do_exit = 1;
	ft_unlink_heredoc(t);
	ft_free_all(t);
}

static void	ft_get_line(t_tr *t)
{
	extern sig_atomic_t		g_sig;

	ft_update_prompt_pwd(t);
	ft_reset_std(t);
	g_sig = 0;
	ft_signal_handler_sigint_rline(t);
	ft_signal_handler_sigquit_ignr(t);
	t->f_line = readline(t->f_prompt);
	ft_signal_all_ignore(t);
	ft_sig_exit_status(t);
	g_sig = 0;
	ft_null_line(t);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_err					e;
	t_tr					t;

	ft_signal_all_ignore_start(argv[0], &t);
	ft_set_error_list(&e, &t);
	ft_set_tracker(argc, argv, envp, &t);
	while (!t.do_exit)
	{
		ft_get_line(&t);
		if (ft_invalid_line(&t))
			continue ;
		ft_get_tokens(&t);
		if (ft_invalid_fields(&t))
			continue ;
		if (ft_heredoc_all(&t))
			continue ;
		ft_execute(0, t.tkn_head, &t);
		ft_signal_all_ignore(&t);
		ft_unlink_heredoc(&t);
		ft_free_2d_int(&t.f_pipes);
		ft_free_tokens(&t);
		ft_free_str(&t.f_line);
	}
	ft_free_all(&t);
	return (0);
}
