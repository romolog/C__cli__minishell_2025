/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_61_utils_nextexec_atoifd_printtkn.c   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:58:07 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/12 16:01:14 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_move_next_execute(int encl, t_tkn **ptr_tkn)
{
	t_tkn	*tkn;

	if (!ptr_tkn || !*ptr_tkn)
		return ;
	tkn = *ptr_tkn;
	while (tkn && !((tkn->brace_close || tkn->ao_and \
					|| tkn->ao_or) && tkn->enclsr == encl) \
				&& !(tkn->pipe && tkn->enclsr == encl))
		tkn = tkn->next;
	if (tkn && tkn->pipe && tkn->enclsr == encl)
		tkn = tkn->next;
	*ptr_tkn = tkn;
}

int	ft_atoi_fd(char *str, t_tr *t)
{
	int		res;

	res = 0;
	ft_err((*str < '0' || *str > '9'), t, __FILE__, __LINE__);
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (FD_MAX - res < ((*str) - '0'))
		{
			t->err = t->err_list->fd_maxnum_overflow;
			ft_e(1, str, NULL, t);
			return (-1);
		}
		res = res * 10 + ((*str) - '0');
		str++;
	}
	ft_err(*str, t, __FILE__, __LINE__);
	return (res);
}

int	ft_is_builtin(char *str)
{
	if (!str || !*str)
		return (0);
	return ((!ft_strncmp(str, "cd", 3) \
				|| !ft_strncmp(str, "echo", 5) \
				|| !ft_strncmp(str, "env", 4) \
				|| !ft_strncmp(str, "export", 7) \
				|| !ft_strncmp(str, "exit", 5) \
				|| !ft_strncmp(str, "pwd", 4) \
				|| !ft_strncmp(str, "unset", 6)));
}

void	ft_print_tokens(int line, char *file, t_tr *t)
{
	t_tkn	*tkn;
	int		len;

	fprintf(stderr, "\n\n----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------\n");
	fflush(stderr);
	fprintf(stderr, "TOKENS:\t\tline: %d\tfile: %s\n", line, file);
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------\n\n");
	fflush(stderr);
	tkn = t->tkn_head;
	if (!tkn)
	{
		fprintf(stderr, "ALL TOKENS ARE DELETED\n\n");
		fflush(stderr);
	}
	while (tkn)
	{
		fprintf(stderr, "\033[0;33m>>|\033[0m");
		fflush(stderr);
		fprintf(stderr, "%s\033[0;33m|<<\033[0m", tkn->f_str);
		fflush(stderr);
		if (tkn->f_str)
			len = ft_strlen(tkn->f_str);
		else
			len = 6;
		len = (len + 6) / 4 - ((len + 6) % 4 == 0 && (len + 6) / 4 > 2);
		while (len < 4)
		{
			fprintf(stderr, "\t");
			fflush(stderr);
			len++;
		}
		fprintf(stderr, "cmd = %d\tbuiltin = %d\t", tkn->w_cmd, tkn->w_bltin);
		fflush(stderr);
		fprintf(stderr, "redir_file = %d\tredir_input = %d\tWILDCARDS = %d\t", \
			tkn->w_redir_file, tkn->redir_input, tkn->exp_wldcrd);
		fflush(stderr);
		fprintf(stderr, "exp_var = %d\n", \
			tkn->exp_env);
		fflush(stderr);		
		tkn = tkn->next;
	}
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------");
	fflush(stderr);
	fprintf(stderr, "----------------------------------\n\n");
	fflush(stderr);
}
