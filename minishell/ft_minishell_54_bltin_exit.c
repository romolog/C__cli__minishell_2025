/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_54_bltin_exit.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:40:44 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:40 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_get_exit_status(t_tkn *tkn, t_tr *t)
{
	char	*str;

	if (!tkn || !tkn->word)
	{
		t->exit_status = 0;
		return (0);
	}
	str = tkn->f_str;
	str += ((*str == '+' || *str == '-') && *(str + 1));
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*tkn->f_str && !*str)
	{
		t->exit_status = (unsigned char)ft_atoi(tkn->f_str);
		return (1);
	}
	else
	{
		t->do_exit = 1;
		ft_strlcpy(t->exit_les, "2", 2);
		t->exit_status = 2;
		t->err = t->err_list->numeric_required;
		ft_e(1, t->f_cmd, tkn->f_str, t);
		return (0);
	}
}

void	ft_bltin_exit(t_tkn *tkn, t_tr *t)
{
	int		valid_exit_arg;

	if (!tkn || !tkn->w_bltin || ft_strncmp(tkn->f_str, "exit", 5))
		return ;
	ft_free_str(&t->f_cmd);
	ft_add_str_malloc(&t->f_cmd, "exit", 4, t);
	t->do_exit = 1;
	tkn = tkn->next;
	valid_exit_arg = ft_get_exit_status(tkn, t);
	if (valid_exit_arg && tkn && tkn->next && tkn->next->word)
	{
		t->do_exit = !t->pid_current;
		ft_strlcpy(t->exit_les, "1", 2);
		t->exit_status = 1;
		t->err = t->err_list->many_args;
		ft_e(1, t->f_cmd, NULL, t);
	}
	if (t->pid_current && !t->pipes_num && t->do_exit)
		write(1, "exit\n", 5);
	else if (t->pid_current && !t->pipes_num && !t->do_exit)
		write(1, "exit, but not\n", 14);
	ft_free_all(t);
}
