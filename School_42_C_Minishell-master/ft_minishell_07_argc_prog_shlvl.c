/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_07_argc_prog_shlvl.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:41:42 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/07 18:32:39 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_check_argc(t_tr *t)
{
	if (t->ac == 1)
		return ;
	t->err = t->err_list->argc;
	ft_e(t->ac > 1, NULL, NULL, t);
	ft_free_str(&t->f_prog);
	close(t->redir_fd_stdin);
	close(t->redir_fd_stderr);
	close(t->redir_fd_stdout);
	exit(EXIT_FAILURE);
}

void	ft_set_tracker_catch_std(t_tr *t)
{
	t->redir_fd_stdin = dup(STDIN_FILENO);
	ft_err(t->redir_fd_stdin < 0, t, __FILE__, __LINE__);
	t->redir_fd_stderr = dup(STDERR_FILENO);
	ft_err(t->redir_fd_stderr < 0, t, __FILE__, __LINE__);
	t->redir_fd_stdout = dup(STDOUT_FILENO);
	ft_err(t->redir_fd_stdout < 0, t, __FILE__, __LINE__);
}

void	ft_set_tracker_prog_name(char *prog_name, t_tr *t)
{
	char	*ptr;

	t->f_prog = NULL;
	ptr = ft_strrchr(prog_name, '/');
	if (!ptr)
		ft_add_str_malloc(&t->f_prog, prog_name, ft_strlen(prog_name), t);
	else
		ft_add_str_malloc(&t->f_prog, ptr + 1, ft_strlen(ptr + 1), t);
}

int	ft_shlvl_atoi(const char *nptr)
{
	long long	res;
	char		*ptr;

	res = 0;
	ptr = (char *)nptr;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\v'\
			|| *ptr == '\f' || *ptr == '\r' || *ptr == '\n')
		ptr++;
	if (*ptr == '+')
		ptr++;
	if (*ptr < '0' || *ptr > '9')
		return (-1);
	while (*ptr == '0')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9' && res < __INT_MAX__)
	{
		res = res * 10 + ((*ptr) - '0');
		ptr++;
	}
	if (res > __INT_MAX__)
		return (-1);
	return (res);
}

void	ft_set_tracker_shell_level(t_tr *t)
{
	int		k;
	char	*f_num;

	f_num = NULL;
	ft_getenv(&f_num, "SHLVL", t);
	if (!f_num || !*f_num)
		k = 1;
	else
	{
		k = ft_shlvl_atoi(f_num);
		if (k >= 0 && k < __INT_MAX__)
			k++;
		else if (k == __INT_MAX__)
			k = 0;
		else
			k = 1;
	}
	ft_free_str(&f_num);
	f_num = ft_itoa(k);
	ft_update_env("SHLVL", f_num, t);
	ft_free_str(&f_num);
}
