/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_04_error_message.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:37:49 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:29:07 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_prog_cmd_arg(char *cmd, char *arg, t_tr *t)
{
	char	*color;

	color = "\033[0;93m";
	write(2, color, ft_strlen(color));
	if (t->f_prog)
	{
		write(2, t->f_prog, ft_strlen(t->f_prog));
		write(2, ": ", 2);
	}
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (t->err)
		write(2, t->err, ft_strlen(t->err));
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n\033[0m", 5);
}

void	ft_w(int condition, char *cmd, t_tr *t)
{
	if (!condition)
	{
		t->err = NULL;
		return ;
	}
	ft_prog_cmd_arg("warning", cmd, t);
	t->err = NULL;
}

void	ft_e(int condition, char *cmd, char *arg, t_tr *t)
{
	if (!condition)
	{
		t->err = NULL;
		return ;
	}
	ft_prog_cmd_arg(cmd, arg, t);
	t->err = NULL;
	errno = 0;
}
