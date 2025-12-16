/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_52_bltin_echo.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:46:34 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:53:23 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_bltin_echo(t_tkn *tkn, t_tr *t)
{
	extern sig_atomic_t		g_sig;	
	int						new_line;

	if (!tkn || !tkn->w_bltin || ft_strncmp(tkn->f_str, "echo", 5))
		return ;
	ft_free_str(&t->f_cmd);
	ft_add_str_malloc(&t->f_cmd, "echo", 4, t);
	ft_signal_handler_sigint_dflt(t);
	ft_signal_handler_sigquit_dflt(t);
	tkn = tkn->next;
	new_line = !tkn || ft_strncmp(tkn->f_str, "-n", 3);
	if (tkn && !ft_strncmp(tkn->f_str, "-n", 3))
		tkn = tkn->next;
	while (!g_sig && tkn && tkn->word)
	{
		if (tkn->word && !tkn->w_redir_fd && tkn->w_arg)
			write(1, tkn->f_str, ft_strlen(tkn->f_str));
		tkn = tkn->next;
		if (tkn && tkn->word)
			write(1, " ", 1);
	}
	if (!g_sig && new_line)
		write(1, "\n", 1);
	ft_strlcpy(t->exit_les, "0", 2);
}
