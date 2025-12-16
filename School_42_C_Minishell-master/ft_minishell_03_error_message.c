/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_03_error_message.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:37:49 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:19:18 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_print_atoi(int num)
{
	char	*str;

	str = ft_itoa(num);
	if (str)
	{
		write(2, str, ft_strlen(str));
		free(str);
	}
}

static void	ft_intro(t_tr *t, char *file_name, int line)
{
	write(2, "\tUsage:\t", 8);
	write(2, t->f_prog, ft_strlen(t->f_prog));
	write(2, "\n\tPrcss:\t", 9);
	if (t->pid_current)
		write(2, "parent", 7);
	else
		write(2, "child", 5);
	write(2, "\n\tFile:\t", 8);
	write(2, file_name, ft_strlen(file_name));
	write(2, "\n\tLine:\t", 8);
	ft_print_atoi(line);
	write(2, "\n\tExit:\t", 9);
	if (t->do_exit)
		ft_print_atoi(t->exit_status);
	else
		write(2, "continue execution", 18);
	if (t->err)
		write(2, "\n\tObj:\t", 7);
	if (t->err)
		write(2, t->err, ft_strlen(t->err));
	write(2, "\n\tErrno:\t", 9);
	ft_print_atoi(errno);
}

void	ft_ctx(int condition, t_tr *t, char *file_name, int line)
{
	if (!condition)
	{
		t->err = NULL;
		return ;
	}
	write(2, "\n\t\033[1;93m____________________________\n\n", 39);
	write(2, "\t\033[1;33mCONTEXT:\033[0;93m\n\n", 25);
	ft_intro(t, file_name, line);
	if (!errno)
		write(2, "\n\tError:\tinvalid object\n", 24);
	else
		perror("\n\n\tErrno:\n\t");
	write(2, "\n\t\033[1;93m____________________________\n\n\n\033[0m", 44);
	t->err = NULL;
	errno = 0;
}

void	ft_err(int condition, t_tr *t, char *file_name, int line)
{
	if (!condition)
	{
		t->err = NULL;
		return ;
	}
	write(2, "\n\t\033[1;93m____________________________\n\n", 39);
	write(2, "\t\033[1;91mERROR:\033[0;93m\n\n", 23);
	t->do_exit = 1;
	if (!t->exit_status)
		t->exit_status = EXIT_FAILURE;
	ft_intro(t, file_name, line);
	if (!errno)
		write(2, "\n\tError:\tinvalid object\n", 24);
	else
		perror("\n\n\tErrno:\n\t");
	write(2, "\n\t\033[1;93m____________________________\n\n\n\033[0m", 44);
	ft_free_all(t);
}

void	ft_err_start(int condition, char *prog_name, t_tr *t)
{
	char	*ptr;

	if (!condition)
	{
		t->err = NULL;
		return ;
	}
	write(2, "\n\t\033[1;93m____________________________\n\n", 39);
	write(2, "\t\033[1;91mERROR START SIGNALS:\033[0;93m\n\n", 23);
	write(2, "\tUsage:\t", 8);
	ptr = ft_strrchr(prog_name, '/') + 1;
	write(2, ptr, ft_strlen(ptr));
	write(2, "\n\tErrno:\t", 9);
	ft_print_atoi(errno);
	perror("\n\n\tErrno:\n\t");
	write(2, "\n\t\033[1;93m____________________________\n\n\n\033[0m", 44);
	exit(EXIT_FAILURE);
}
