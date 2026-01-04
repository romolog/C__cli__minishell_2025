/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_39_execute_bltin.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:49:22 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:35:20 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_call_builtin(t_tkn *tkn, t_tr *t)
{
	if (!ft_strncmp(tkn->f_str, "cd", 3))
		ft_bltin_chdir(tkn, t);
	else if (!ft_strncmp(tkn->f_str, "echo", 5))
		ft_bltin_echo(tkn, t);
	else if (!ft_strncmp(tkn->f_str, "env", 4))
		ft_bltin_env(tkn, t);
	else if (!ft_strncmp(tkn->f_str, "exit", 5))
		ft_bltin_exit(tkn, t);
	else if (!ft_strncmp(tkn->f_str, "export", 7))
		ft_bltin_export(tkn, t);
	else if (!ft_strncmp(tkn->f_str, "pwd", 4))
		ft_bltin_pwd(tkn, t);
	else if (!ft_strncmp(tkn->f_str, "unset", 6))
		ft_bltin_unset(tkn, t);
}

int	ft_execute_builtin(t_tkn *tkn, t_tr *t)
{
	if (!tkn)
		return (0);
	if (ft_is_builtin(tkn->f_str))
		ft_call_builtin(tkn, t);
	else
		return (0);
	return (1);
}
