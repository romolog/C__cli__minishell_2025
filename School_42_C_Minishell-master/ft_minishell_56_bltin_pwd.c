/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_56_bltin_pwd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:42:12 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:32 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_bltin_pwd(t_tkn *tkn, t_tr *t)
{
	if (!tkn || !tkn->w_bltin || ft_strncmp(tkn->f_str, "pwd", 4))
		return ;
	ft_free_str(&t->f_cwd);
	t->f_cwd = getcwd(NULL, 0);
	ft_err(!t->f_cwd, t, __FILE__, __LINE__);
	write(1, t->f_cwd, ft_strlen(t->f_cwd));
	write(1, "\n", 1);
	ft_strlcpy(t->exit_les, "0", 2);
}
