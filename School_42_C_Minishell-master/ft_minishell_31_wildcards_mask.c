/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_31_wildcards_mask.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:23:39 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/11 17:40:34 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_expand_wildcards_mask(t_tkn *tkn, t_tr *t)
{
	char	*exp;
	size_t	len;

	if (!tkn || !tkn->f_str || !*tkn->f_str)
		return (-1);
	exp = tkn->f_str;
	while (*exp && (!ft_strncmp(exp, "./", 2) || *exp == '/'))
	{
		exp += 2 * (!ft_strncmp(exp, "./", 2));
		exp += (*exp == '/');
	}
	if (!ft_strncmp(exp, "..", 2) || ft_strchr(exp, '/'))
	{
		t->err = t->err_list->wldcrds_cwd_only;
		ft_e(1, NULL, NULL, t);
		return (-1);
	}
	len = exp - tkn->f_str;
	if (!len)
		return (0);
	ft_add_str_malloc(&t->f_wldcrd_mask, tkn->f_str, len, t);
	return (len);
}

static int	ft_count_wldcrds_split(char *wc, t_tr *t)
{
	int		count;
	int		i;
	int		done;

	ft_reset_qds(t);
	count = 0;
	while (*wc)
	{
		done = 0;
		while (*wc && *wc == '*')
			wc++;
		while (*wc && *wc != '*')
		{
			i = 0;
			wc += ft_quotes_status(wc, t);
			while (wc[i] && ((t->qd_on && wc[i] != '\"') || \
				(t->qs_on && wc[i] != '\'') || (!t->qd_on && !t->qs_on \
				&& wc[i] != '\"' && wc[i] != '\'' && wc[i] != '*')))
				i++;
			wc += i;
			done += (i != 0);
		}
		count += (done != 0);
	}
	return (count);
}

//	RETURN:	NULL if wildcard is ""''*'' = *
void	ft_expand_wildcards_split(char *wc, char ***f_arr, t_tr *t)
{
	int		num;
	int		i;
	int		k;

	ft_err(!wc || !*wc, t, __FILE__, __LINE__);
	num = ft_count_wldcrds_split(wc, t);
	if (!num)
		return ;
	*f_arr = ft_calloc(num + 1, sizeof(char *));
	k = 0;
	while (*wc && k < num)
	{
		while (*wc && *wc == '*')
			wc++;
		wc += ft_quotes_status(wc, t);
		i = 0;
		while (wc[i] && ((t->qd_on && wc[i] != '\"') || \
			(t->qs_on && wc[i] != '\'') || (!t->qd_on && !t->qs_on \
			&& wc[i] != '\"' && wc[i] != '\'' && wc[i] != '*')))
			i++;
		if (i)
			ft_add_str_malloc((*f_arr) + k, wc, i, t);
		wc += i;
		k += ((*f_arr)[k] && (*f_arr)[k][0] && (*wc == '*' || !*wc));
	}
}

int	ft_is_match_wildcards(char *wc, char **f_arr, char *fn)
{
	int		i;

	if (!f_arr)
		return (1);
	if (*wc != '*' && ft_strncmp(fn, f_arr[0], ft_strlen(f_arr[0])))
		return (0);
	i = -1;
	while (f_arr[++i] && fn && *fn)
	{
		while (*fn && ft_strncmp(fn, f_arr[i], ft_strlen(f_arr[i])))
			fn++;
		if (ft_strncmp(fn, f_arr[i], ft_strlen(f_arr[i])))
			return (0);
		fn += ft_strlen(f_arr[i]);
	}
	if (f_arr[i])
		return (0);
	if (wc[ft_strlen(wc) - 1] == '*' || !*fn)
		return (1);
	return (0);
}
