/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_60_utils_env_quotes.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:58:07 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/06 16:12:14 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_add_entry_env(int i, t_tr *t)
{
	char	**arr;
	int		k;

	if (t->f_env && t->f_env[i])
		return ;
	arr = malloc(sizeof(char *) * (i + 2));
	ft_err(!arr, t, __FILE__, __LINE__);
	k = -1;
	while (++k < i)
		arr[k] = t->f_env[k];
	arr[i] = NULL;
	arr[i + 1] = NULL;
	free(t->f_env);
	t->f_env = arr;
}

void	ft_update_env(char *env_name, char *update_str, t_tr *t)
{
	int		i;
	char	*f_ename;

	i = 0;
	if (!env_name || !*env_name || !update_str)
		return ;
	f_ename = NULL;
	ft_add_str_malloc(&f_ename, env_name, ft_strlen(env_name), t);
	if (env_name[ft_strlen(env_name) - 1] != '=')
		ft_add_str_malloc(&f_ename, "=", 1, t);
	while (t->f_env[i] && \
		ft_strncmp(t->f_env[i], f_ename, ft_strlen(f_ename)))
		i++;
	ft_add_entry_env(i, t);
	ft_free_str(t->f_env + i);
	ft_add_str_malloc(t->f_env + i, f_ename, ft_strlen(f_ename), t);
	ft_add_str_malloc(t->f_env + i, update_str, ft_strlen(update_str), t);
	ft_free_str(&f_ename);
}

char	*ft_getenv(char **dst, char *env_name, t_tr *t)
{
	int		i;
	size_t	len;
	size_t	len_ename;
	char	*f_ename;

	len_ename = ft_strlen(env_name);
	f_ename = NULL;
	ft_add_str_malloc(&f_ename, env_name, len_ename, t);
	if (f_ename[len_ename - 1] != '=')
	{
		ft_add_str_malloc(&f_ename, "=", 1, t);
		len_ename++;
	}
	i = 0;
	while (t->f_env[i] && \
		ft_strncmp(t->f_env[i], f_ename, len_ename))
		i++;
	ft_free_str(dst);
	if (t->f_env[i])
	{
		len = ft_strlen(t->f_env[i]) - len_ename;
		ft_add_str_malloc(dst, t->f_env[i] + len_ename, len, t);
	}
	ft_free_str(&f_ename);
	return (*dst);
}

//	updates status of qd_on and qs_on
//	RETURN: 1 if status updated, 0 if not
int	ft_quotes_status(char *exp, t_tr *t)
{
	int	done;

	if (!exp || !*exp)
		return (0);
	done = 0;
	done += ((*exp == '\'' || *exp == '\"') && !t->qd_on && !t->qs_on);
	t->qd_on += (*exp == '\"' && !t->qd_on && !t->qs_on);
	t->qs_on += (*exp == '\'' && !t->qd_on && !t->qs_on);
	done -= (!done \
		&& ((*exp == '\"' && t->qd_on) || (*exp == '\'' && t->qs_on)));
	t->qd_on -= (done == -1 && *exp == '\"' && t->qd_on);
	t->qs_on -= (done == -1 && *exp == '\'' && t->qs_on);
	return (done != 0);
}

void	ft_reset_std(t_tr *t)
{
	dup2(t->redir_fd_stdin, STDIN_FILENO);
	dup2(t->redir_fd_stderr, STDERR_FILENO);
	dup2(t->redir_fd_stdout, STDOUT_FILENO);
}
