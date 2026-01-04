/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:13:07 by rponomar          #+#    #+#             */
/*   Updated: 2024/10/06 17:01:00 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getline.h"

void	ft_free_arc(t_arc **arc)
{
	t_arc	*temp;

	free((*arc)->str);
	if ((*arc)->next - (*arc) == 0)
	{
		free(*arc);
		(*arc) = NULL;
		return ;
	}
	((*arc)->prev)->next = (*arc)->next;
	((*arc)->next)->prev = (*arc)->prev;
	temp = (*arc)->next;
	free((*arc));
	(*arc) = temp;
	(*arc)->start = 1;
}

static void	ft_set_new_arc(t_track *t, t_arc **arc, int fd)
{
	t_arc	*new_arc;

	new_arc = malloc(sizeof(t_arc));
	if (!new_arc)
	{
		free(t->str);
		t->str = NULL;
		return ;
	}
	new_arc->fd = fd;
	new_arc->start = 1;
	if (!*arc)
	{
		new_arc->next = new_arc;
		new_arc->prev = new_arc;
	}
	else
	{
		new_arc->next = (*arc)->next;
		new_arc->prev = *arc;
		((*arc)->next)->prev = new_arc;
		(*arc)->next = new_arc;
		(*arc)->start = 0;
	}
	*arc = new_arc;
}

static void	ft_str_to_arc(t_track *t, t_arc *arc, size_t i)
{
	size_t	k;

	arc->str = malloc((t->read - (i + 1)) + 1);
	if (!arc->str)
	{
		free(t->str);
		t->str = NULL;
		return ;
	}
	k = -1;
	while (t->str[t->len + ++k])
		arc->str[k] = t->str[t->len + k];
	arc->str[k] = '\0';
}

void	ft_get_str(t_track *t, t_arc **arc, int fd)
{
	size_t	i;

	i = 0;
	while (t->str[t->len + i] != '\n' && t->str[t->len + i])
		i++;
	t->done += (t->read != BUFFER_SIZE && i == (size_t)t->read) \
				+ (t->str[t->len + i] == '\n');
	t->len += (i + (i != (size_t)t->read));
	if (t->str[t->len])
	{
		ft_set_new_arc(t, arc, fd);
		ft_str_to_arc(t, *arc, i);
	}
	ft_adjust_str(t);
}
