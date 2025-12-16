/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_30_expand_wildcards.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:23:39 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 14:34:03 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_rec(char *fn, int mask_len, t_tkn *tkn, t_tr *t)
{
	t_tkn	*temp;

	ft_free_str(&tkn->f_str);
	ft_add_str_malloc(&tkn->f_str, t->f_wldcrd_mask, mask_len, t);
	ft_add_str_malloc(&tkn->f_str, fn, ft_strlen(fn), t);
	temp = ft_calloc(1, sizeof(t_tkn));
	ft_err(!temp, t, __FILE__, __LINE__);
	temp->f_str = NULL;
	temp->word = 1;
	temp->enclsr = tkn->enclsr;
	if (tkn->next)
		tkn->next->prev = temp;
	temp->next = tkn->next;
	tkn->next = temp;
	temp->prev = tkn;
}

static void	ft_expand_to_names(int mask_len, char **fns, t_tkn *tkn, t_tr *t)
{
	int		i;
	char	**f_arr;
	char	*f_wc;

	f_arr = NULL;
	f_wc = NULL;
	ft_add_str_malloc(&f_wc, tkn->f_str + mask_len, \
				ft_strlen(tkn->f_str + mask_len), t);
	ft_expand_wildcards_split(f_wc, &f_arr, t);
	i = -1;
	while (fns[++i])
	{
		if (fns[i][0] == '.' && fns[i][0] != *f_wc)
			continue ;
		if (ft_is_match_wildcards(f_wc, f_arr, fns[i]))
			ft_rec(fns[i], mask_len, tkn, t);
	}
	ft_free_2d_char(&f_arr);
	ft_free_str(&f_wc);
}

void	ft_expand_wildcards(int encl, t_tkn *tkn, t_tr *t)
{
	char	**f_names;
	int		mask_len;

	if (!t->tkn_head || !tkn)
		return ;
	f_names = NULL;
	while (tkn && !((tkn->brace_close || tkn->ao_and \
		|| tkn->ao_or) && tkn->enclsr == encl))
	{
		if (tkn->word && tkn->exp_wldcrd && tkn->enclsr == encl)
		{
			mask_len = ft_expand_wildcards_mask(tkn, t);
			if (mask_len >= 0)
			{
				ft_get_cwd_names(&f_names, t);
				ft_expand_to_names(mask_len, f_names, tkn, t);
				ft_free_2d_char(&f_names);
			}
		}
		ft_expand_wildcards_process_tkn(&tkn, t);
	}
}
