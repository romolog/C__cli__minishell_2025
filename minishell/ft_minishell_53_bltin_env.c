/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_53_bltin_env.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:00:26 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:45 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_bltin_env(t_tkn *tkn, t_tr *t)
{
	int		i;

	if (!tkn || !tkn->w_bltin || ft_strncmp(tkn->f_str, "env", 4))
		return ;
	ft_free_str(&t->f_cmd);
	ft_add_str_malloc(&t->f_cmd, "env", 3, t);
	if (tkn->next && tkn->next->word && !tkn->next->w_redir_fd)
	{
		ft_strlcpy(t->exit_les, "1", 2);
		t->err = t->err_list->many_args;
		ft_e(1, t->f_cmd, NULL, t);
		return ;
	}
	i = -1;
	while (t->f_env[++i])
	{
		if (i)
			write(1, "\n", 1);
		write(1, t->f_env[i], ft_strlen(t->f_env[i]));
	}
	write(1, "\n", 1);
	ft_strlcpy(t->exit_les, "0", 2);
}
