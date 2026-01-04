/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_19_fields.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:26:22 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 13:55:58 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_index_enclosure(int *fail, t_tkn *tkn, t_tr *t)
{
	int		encl;

	encl = 0;
	while (!*fail && tkn)
	{
		if (tkn->brace_close)
			tkn->enclsr = encl;
		encl += tkn->brace_open - tkn->brace_close;
		if (encl < 0)
		{
			*fail = 1;
			break ;
		}
		if (encl > t->token_max_enclsr)
			t->token_max_enclsr = encl;
		if (!tkn->brace_close)
			tkn->enclsr = encl;
		tkn = tkn->next;
	}
	if (encl)
		*fail = 1;
}

static void	ft_braces_outside(int *fail, t_tkn *tkn)
{
	while (!*fail && tkn)
	{
		if (tkn->brace_open && tkn->prev && !(tkn->prev->pipe \
			|| tkn->prev->brace_open || tkn->prev->ao_and || tkn->prev->ao_or))
			(*fail)++;
		else if (tkn->brace_open && (!tkn->next || tkn->next->brace_close))
			(*fail)++;
		if (tkn->brace_close && tkn->next && !(tkn->next->pipe \
			|| tkn->next->brace_close || tkn->next->ao_and || tkn->next->ao_or))
			(*fail)++;
		tkn = tkn->next;
	}
}

static void	ft_invalid_fields_braces(int *fail, t_tkn *tkn, t_tr *t)
{
	t_tkn	*ptr;
	int		encl;

	ft_index_enclosure(fail, tkn, t);
	ft_braces_outside(fail, tkn);
	while (!*fail && tkn)
	{
		if (tkn->brace_open && tkn->next->brace_open)
		{
			encl = tkn->enclsr;
			ptr = tkn->next->next;
			while (!(ptr->brace_close && ptr->enclsr == encl + 1))
				ptr = ptr->next;
			*fail = 1;
			while (*fail && !(ptr->brace_close && ptr->enclsr == encl))
			{
				ptr = ptr->next;
				*fail -= ptr->enclsr == encl \
					&& (ptr->ao_and || ptr->ao_or || ptr->pipe);
			}
		}
		tkn = tkn->next;
	}
	t->err = t->err_list->syntax_err;
	ft_e(*fail, "invalid braces", NULL, t);
}

int	ft_invalid_fields(t_tr *t)
{
	int	fail;

	fail = 0;
	// fprintf(stderr, "\n\tinv fields\tSTART fail = %d\n\n", fail);			
	if (!t->tkn_head)
		return (1);
	ft_invalid_fields_braces(&fail, t->tkn_head, t);
	// fprintf(stderr, "\n\tinv fields\tafter braces fail = %d\n\n", fail);	
	ft_invalid_fields_andor(&fail, t->tkn_head, t);
	// fprintf(stderr, "\n\tinv fields\tafter andor fail = %d\n\n", fail);	
	ft_invalid_fields_pipe(&fail, t->tkn_head, t);
	// fprintf(stderr, "\n\tinv fields\tafter pipe fail = %d\n\n", fail);
	ft_invalid_fields_redirection(&fail, t->tkn_head, t);
	if (fail)
	{
		t->exit_status = 2;
		ft_strlcpy(t->exit_les, "2", 2);
		ft_free_str(&t->f_line);
		ft_free_tokens(t);
	}
	return (fail);
}
