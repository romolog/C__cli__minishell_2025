/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_55_bltin_export.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:53:15 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/10 20:00:31 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_is_name(int i, char *str, t_tr *t)
{
	int	k;

	if (!str || !*str || !i)
	{
		t->err = t->err_list->invalid_name;
		ft_e(1, t->f_cmd, str, t);
		return (0);
	}
	k = -1;
	while (str[++k] && k < i)
	{
		if ((str[k] < 'a' || str[k] > 'z') \
			&& (str[k] < 'A' || str[k] > 'Z') \
			&& ((str[k] < '0' || str[k] > '9') || !k) \
			&& str[k] != '_')
		{
			t->err = t->err_list->invalid_name;
			ft_e(1, t->f_cmd, str, t);
			t->exit_status = 1;
			ft_strlcpy(t->exit_les, "1", 2);
			return (0);
		}
	}
	return (1);
}

static void	ft_assign_value(int i, t_tkn *tkn, t_tr *t)
{
	char	*f_env_name;
	char	*f_update_str;
	char	*v;

	f_env_name = NULL;
	ft_add_str_malloc(&f_env_name, tkn->f_str, i, t);
	f_update_str = NULL;
	v = tkn->f_str + i + 1;
	if (*v)
		ft_add_str_malloc(&f_update_str, v, ft_strlen(v), t);
	else
		ft_add_str_malloc(&f_update_str, "", 0, t);
	ft_update_env(f_env_name, f_update_str, t);
	ft_free_str(&f_env_name);
	ft_free_str(&f_update_str);
}

static void	ft_export_var(t_tkn *tkn, t_tr *t)
{
	int	i;

	i = 0;
	while (tkn->f_str[i] && tkn->f_str[i] != '=')
		i++;
	if (!ft_is_name(i, tkn->f_str, t))
	{
		ft_strlcpy(t->exit_les, "1", 2);
		t->exit_status = 1;
		return ;
	}
	if (!tkn->f_str[i])
		return ;
	ft_assign_value(i, tkn, t);
}

void	ft_bltin_export(t_tkn *tkn, t_tr *t)
{
	if (!tkn || !tkn->w_bltin || ft_strncmp(tkn->f_str, "export", 7))
		return ;
	ft_strlcpy(t->exit_les, "0", 2);
	t->exit_status = 0;
	if (!tkn->next)
		return ;
	ft_free_str(&t->f_cmd);
	ft_add_str_malloc(&t->f_cmd, "export", 6, t);
	tkn = tkn->next;
	while (tkn && tkn->word)
	{
		ft_export_var(tkn, t);
		tkn = tkn->next;
	}
}

// static int	ft_passby(char *exp, char **dst, t_tr *t)
// {
// 	int		i;
//
// 	i = 0;
// 	while (t->qs_on && exp[i] && exp[i] != '\'')
// 		i++;
// 	while (t->qd_on && exp[i] && exp[i] != '\"')
// 		i++;
// 	while (exp[i] && exp[i] != '\"' && exp[i] != '\'')
// 		i++;
// 	if (i)
// 		ft_add_str_malloc(dst, exp, i, t);
// 	return (i);
// }

// static void	ft_assign_value(int i, t_tkn *tkn, t_tr *t)
// {
// 	char	*f_env_name;
// 	char	*f_update_str;
// 	char	*v;
//
// 	f_env_name = NULL;
// 	ft_add_str_malloc(&f_env_name, tkn->f_str, i, t);
// 	f_update_str = NULL;
// 	v = tkn->f_str + i + 1;
// 	fprintf(stderr, "\n\tassign value:\tvalue is >>|%s|<<\n\n", v);
// 	ft_reset_qds(t);
// 	while (*v)
// 	{
// 		v += ft_quotes_status(v, t);
// 		v += ft_passby(v, &f_update_str, t);
// 	}
// 	if (!*v)
// 		ft_add_str_malloc(&f_update_str, "", 0, t);
// 	ft_update_env(f_env_name, f_update_str, t);
// 	ft_free_str(&f_env_name);
// 	ft_free_str(&f_update_str);
// }