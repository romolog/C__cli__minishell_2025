/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_45_execute_is_directory_is_execfile.c :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:14:12 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/11 16:50:41 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

//	RETURN:	>= 1	: MAYBE it is a directory
//	RETURN:	==1		: directory ok
//	RETURN:	>1		: dir or some dir in the path with error (access)
//	RETURN:	<= 0 : no, it is not a directory	
//	dir_check = NULL if error
//	dir_check = (DIR *) pointer if success
int	ft_is_directory(char *name, t_tr *t)
{
	DIR		*dir_check;
	int		res;
	int		errnum;

	if (!name || !*name)
		return (-2);
	errno = 0;
	errnum = 0;
	dir_check = opendir(name);
	errnum = errno;
	if (dir_check)
		ft_err(closedir(dir_check) == -1, t, __FILE__, __LINE__);
	ft_set_errno_messages(errnum, t);
	if (errnum == ENOENT)
		return (-1);
	if (errnum == ENOTDIR)
		return (0);
	if (!errnum && !access(name, X_OK))
		res = 1;
	else if (!errnum && access(name, X_OK))
		res = EACCES + 1;
	else
		res = errnum + 1;
	return (res);
}

int	ft_is_exec_file(char *name, t_tr *t)
{
	if (!name || !*name)
		return (-2);
	else if (access(name, F_OK))
		return (-1);
	else if (!access(name, X_OK) && ft_is_directory(name, t) <= 0)
		return (1);
	else if (!access(name, F_OK) && access(name, X_OK) \
		&& ft_is_directory(name, t) <= 0)
		return (EACCES);
	else
		return (0);
}
