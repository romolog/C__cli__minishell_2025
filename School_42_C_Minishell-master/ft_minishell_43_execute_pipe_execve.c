/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_43_execute_pipe_execve.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:51:28 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/10 21:33:07 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_set_cmd_args(t_tkn *tkn, t_tr *t)
{
	int		i;
	t_tkn	*ptr;

	ptr = tkn;
	free(t->f_cmd_args);
	i = 0;
	while (ptr && !(ptr->brace_close || ptr->pipe || ptr->ao_and || ptr->ao_or))
	{
		i++;
		ptr = ptr->next;
	}
	t->f_cmd_args = ft_calloc(i + 1, sizeof(char *));
	ft_err(!t->f_cmd_args, t, __FILE__, __LINE__);
	t->f_cmd_args[0] = t->f_cmd;
	t->f_cmd_args[i] = NULL;
	tkn = tkn->next;
	i = 1;
	while (tkn && !(tkn->brace_close || tkn->pipe || tkn->ao_and || tkn->ao_or))
	{
		t->f_cmd_args[i] = tkn->f_str;
		i++;
		tkn = tkn->next;
	}
}

static void	ft_isvalid_path(int found, t_tr *t)
{
	int		is_directory;
	int		is_exec_file;

	is_directory = ft_is_directory(t->f_cmd_path, t);
	is_exec_file = ft_is_exec_file(t->f_cmd_path, t);
	if (is_exec_file != 1 || is_directory > 0)
	{
		if ((is_exec_file != 1 && found) || is_directory > 0)
		{
			t->err = t->err_list->perm_denied;
			if (is_directory)
				t->err = t->err_list->is_dir;
			ft_strlcpy(t->exit_les, "126", 4);
			t->exit_status = 126;
		}
		else if (is_exec_file != 1)
		{
			t->err = t->err_list->cmd_notfound;
			ft_strlcpy(t->exit_les, "127", 4);
			t->exit_status = 127;
		}
		ft_e(1, t->f_cmd, NULL, t);
		t->do_exit = 1;
		ft_free_all(t);
	}
}

static void	ft_get_cmd_path(char **f_p, t_tr *t)
{
	char	*path;
	size_t	i;
	int		found;

	found = 0;
	if (f_p && *f_p && **f_p)
	{
		path = ft_getenv(&t->f_path, "PATH", t);
		while ((ft_is_exec_file(*f_p, t) != 1 || !ft_strchr(*f_p, '/')) \
			&& path && *path)
		{
			i = 0;
			while (path[i] && path[i] != ':')
				i++;
			ft_free_str(f_p);
			ft_add_str_malloc(f_p, path, i, t);
			if ((*f_p)[i] != '/')
				ft_add_str_malloc(f_p, "/", 1, t);
			ft_add_str_malloc(f_p, t->f_cmd, ft_strlen(t->f_cmd), t);
			found += (!found && ft_is_exec_file(*f_p, t) >= 1);
			path += i + (path[i] == ':');
		}
	}
	ft_isvalid_path(found, t);
}

// ENOEXEC = 8	Exec format error (POSIX.1-2001)
//				means file is executable, but either empty 
//				or something wrong with env
void	ft_execute_pipe_child_cmd_call_execve(t_tkn **tkn, t_tr *t)
{
	ft_execute_pipe_child_simplify_path(t);
	if (!ft_strncmp(t->f_cmd_path, "./", 2) || *t->f_cmd_path == '/')
		ft_isvalid_path(1, t);
	else
		ft_get_cmd_path(&t->f_cmd_path, t);
	ft_set_cmd_args(*tkn, t);
	ft_signal_handler_sigint_dflt(t);
	ft_signal_handler_sigquit_dflt(t);
	execve(t->f_cmd_path, t->f_cmd_args, t->f_env);
	if (errno == ENOEXEC)
	{
		ft_strlcpy(t->exit_les, "0", 2);
		t->exit_status = 0;
		t->do_exit = 1;
		ft_free_all(t);
	}
	ft_err(1, t, __FILE__, __LINE__);
}
