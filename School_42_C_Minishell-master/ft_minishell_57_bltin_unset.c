/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_57_bltin_unset.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:28:19 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_delete_entry_env(int i, t_tr *t)
{
	int		num;
	int		k;
	char	**arr;

	num = 0;
	while (t->f_env[num])
		num++;
	num--;
	arr = malloc(sizeof(char *) * (num + 1));
	arr[num] = NULL;
	k = -1;
	while (++k < i)
		arr[k] = t->f_env[k];
	k--;
	ft_free_str(t->f_env + i);
	while (++k < num)
		arr[k] = t->f_env[k + 1];
	free(t->f_env);
	t->f_env = arr;
}

static void	ft_do_unset(t_tkn *tkn, t_tr *t)
{
	char	*f_env_name;
	size_t	i;
	size_t	len;

	ft_strlcpy(t->exit_les, "0", 2);
	if (!*tkn->f_str)
		return ;
	ft_strlcpy(t->exit_les, "1", 2);
	f_env_name = NULL;
	ft_add_str_malloc(&f_env_name, tkn->f_str, ft_strlen(tkn->f_str), t);
	ft_add_str_malloc(&f_env_name, "=", 1, t);
	len = ft_strlen(f_env_name);
	i = 0;
	while (t->f_env[i] && ft_strncmp(t->f_env[i], f_env_name, len))
		i++;
	if (t->f_env[i])
		ft_delete_entry_env(i, t);
	ft_free_str(&f_env_name);
	ft_strlcpy(t->exit_les, "0", 2);
}

void	ft_bltin_unset(t_tkn *tkn, t_tr *t)
{
	if (!tkn || !tkn->w_bltin || ft_strncmp(tkn->f_str, "unset", 6))
		return ;
	ft_strlcpy(t->exit_les, "0", 2);
	if (!tkn->next || !tkn->next->word)
		return ;
	tkn = tkn->next;
	while (tkn && tkn->word)
	{
		ft_do_unset(tkn, t);
		tkn = tkn->next;
	}
}
