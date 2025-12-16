/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_59_utils_exec.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:10:49 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/07 20:53:09 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_get_cmd(char ***args, char *cmd_line, t_tr *t)
{
	size_t	i;
	char	*ptr;

	(*args) = ft_split(cmd_line, ' ');
	ft_err(!(*args), t, __FILE__, __LINE__);
	ptr = t->f_path_start;
	while (*ptr && access(**args, X_OK))
	{
		i = 0;
		while (ptr[i] && ptr[i] != ':')
			i++;
		ft_add_str_malloc(&t->f_cmd, ptr, i, t);
		ft_add_str_malloc(&t->f_cmd, "/", 1, t);
		ft_add_str_malloc(&t->f_cmd, **args, ft_strlen(**args), t);
		if (!access(t->f_cmd, X_OK))
			break ;
		ft_free_str(&t->f_cmd);
		ptr += i + (ptr[i] == ':');
	}
	if (t->f_cmd)
		ft_free_str(*args);
	if (t->f_cmd)
		**args = t->f_cmd;
	t->f_cmd = NULL;
	return (!access(**args, X_OK));
}

static char	**ft_read_file(int fd, t_tr *t)
{
	char	**f_arr;
	char	*s;
	char	*f_str;

	f_str = NULL;
	s = ft_get_next_line(fd);
	while (s)
	{
		ft_add_str_malloc(&f_str, s, ft_strlen(s), t);
		ft_add_str_malloc(&f_str, "\n", 1, t);
		ft_free_str(&s);
		s = ft_get_next_line(fd);
	}
	f_arr = ft_split(f_str, '\n');
	ft_err(!f_arr, t, __FILE__, __LINE__);
	free(f_str);
	return (f_arr);
}

void	ft_if_execve_fails(t_tr *t)
{
	int		errnum;

	errnum = errno;
	ft_err(close(STDOUT_FILENO) == -1, t, __FILE__, __LINE__);
	errno = errnum;
	ft_err(1, t, __FILE__, __LINE__);
}

void	ft_exec(char ***f_dst, char *cmd_line, t_tr *t)
{
	char	**args;
	int		pid;
	int		fd[2];

	ft_err(pipe(fd), t, __FILE__, __LINE__);
	pid = fork();
	ft_err(pid == -1, t, __FILE__, __LINE__);
	if (!pid)
	{
		ft_err(!ft_get_cmd(&args, cmd_line, t), t, __FILE__, __LINE__);
		ft_free_close_fd(fd + 0, t);
		ft_err(dup2(fd[1], STDOUT_FILENO) < 0, t, __FILE__, __LINE__);
		ft_free_close_fd(fd + 1, t);
		ft_close_catched_stds(t);
		execve(args[0], args, __environ);
		ft_if_execve_fails(t);
	}
	ft_free_close_fd(fd + 1, t);
	ft_err(wait(NULL) == -1, t, __FILE__, __LINE__);
	*f_dst = ft_read_file(fd[0], t);
	ft_free_close_fd(fd + 0, t);
}
