/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_05_error_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:07:50 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/01 12:19:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_set_list_1(t_err *e)
{
	char	*str;

	str = "Requires no argument";
	ft_strlcpy(e->argc, str, ft_strlen(str) + 1);
	str = "Command not found";
	ft_strlcpy(e->cmd_notfound, str, ft_strlen(str) + 1);
	str = "Empty argument";
	ft_strlcpy(e->empty_arg, str, ft_strlen(str) + 1);
	str = "PATH empty... once again how you did it?";
	ft_strlcpy(e->empty_env_path, str, ft_strlen(str) + 1);
	str = "HOSTNAME empty... let's repeat it?";
	ft_strlcpy(e->empty_host, str, ft_strlen(str) + 1);
	str = "Prompt empty... you did destroy a good thing, please show it again?";
	ft_strlcpy(e->empty_prompt, str, ft_strlen(str) + 1);
	str = "USER empty... please break it again one more time?";
	ft_strlcpy(e->empty_user, str, ft_strlen(str) + 1);
	str = "Redirection fd max quantity is exceeded";
}

static void	ft_set_list_2(t_err *e)
{
	char	*str;

	str = "Redirection fd max quantity is exceeded";
	ft_strlcpy(e->fd_num_exceeded, str, ft_strlen(str) + 1);
	str = "Redirection fd max = 1023 is exceeded";
	ft_strlcpy(e->fd_maxnum_overflow, str, ft_strlen(str) + 1);
	str = "Here_doc delimited by EOF (wanted 'LIM')";
	ft_strlcpy(e->heredoc_eof, str, ft_strlen(str) + 1);
	str = "Not a valid identifier";
	ft_strlcpy(e->invalid_name, str, ft_strlen(str) + 1);
	str = "Is a directory";
	ft_strlcpy(e->is_dir, str, ft_strlen(str) + 1);
	str = "Too many arguments";
	ft_strlcpy(e->many_args, str, ft_strlen(str) + 1);
	str = "Numeric argument required";
	ft_strlcpy(e->numeric_required, str, ft_strlen(str) + 1);
	str = "No such file or directory";
	ft_strlcpy(e->no_file, str, ft_strlen(str) + 1);
	str = "Not a directory";
	ft_strlcpy(e->not_dir, str, ft_strlen(str) + 1);
}

static void	ft_set_list_3(t_err *e)
{
	char	*str;

	str = "Datatype overflow";
	ft_strlcpy(e->overflow, str, ft_strlen(str) + 1);
	str = "Permission denied";
	ft_strlcpy(e->perm_denied, str, ft_strlen(str) + 1);
	str = "Syntax error";
	ft_strlcpy(e->syntax_err, str, ft_strlen(str) + 1);
	str = "Unmatched quote";
	ft_strlcpy(e->unmatched_quote, str, ft_strlen(str) + 1);
	str = "HOME not set";
	ft_strlcpy(e->unset_home, str, ft_strlen(str) + 1);
	str = "OLDPWD not set";
	ft_strlcpy(e->unset_oldpwd, str, ft_strlen(str) + 1);
	str = "Wildcards work ONLY for the current working directory";
	ft_strlcpy(e->wldcrds_cwd_only, str, ft_strlen(str) + 1);
}

void	ft_set_error_list(t_err *e, t_tr *t)
{
	t->err_list = e;
	t->err = NULL;
	ft_set_list_1(e);
	ft_set_list_2(e);
	ft_set_list_3(e);
}
