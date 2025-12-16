/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:12:46 by rponomar          #+#    #+#             */
/*   Updated: 2024/10/28 19:00:22 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getline.h"

static int	ft_set_track(t_track *track)
{
	track->done = 0;
	track->len = 0;
	track->read = 0;
	track->str = malloc(BUFFER_SIZE + 1);
	if (!track->str)
		return (0);
	track->str[0] = 0;
	return (1);
}

static int	ft_get_arc(t_arc **arc, int fd)
{
	if (!*arc)
		return (0);
	if ((*arc)->fd == fd)
		return (1);
	(*arc) = (*arc)->next;
	while ((*arc)->fd != fd && !(*arc)->start)
		(*arc) = (*arc)->next;
	if ((*arc)->fd == fd)
	{
		(*arc)->start = 1;
		(*arc) = (*arc)->next;
		while (!(*arc)->start)
			(*arc) = (*arc)->next;
		(*arc)->start = 0;
		while (!(*arc)->start)
			(*arc) = (*arc)->next;
		return (1);
	}
	return (0);
}

void	ft_adjust_str(t_track *t)
{
	char	*temp;
	size_t	size;
	size_t	i;

	size = (t->len + 1 + BUFFER_SIZE * (!t->done));
	size *= (t->len + 1 <= (t->len + 1 + BUFFER_SIZE * (!t->done)));
	temp = malloc(size);
	if (!temp && !t->done)
	{
		free(t->str);
		t->str = NULL;
	}
	if (!temp)
		return ;
	temp[t->len] = '\0';
	temp[t->len + BUFFER_SIZE * (!t->done)] = '\0';
	i = -1;
	while (++i < t->len)
		temp[i] = t->str[i];
	free(t->str);
	t->str = temp;
}

static void	ft_arc_to_str(t_track *t, t_arc **arc)
{
	size_t	i;
	size_t	k;

	i = -1;
	while ((*arc)->str[++i] != '\n' && (*arc)->str[i])
		t->str[i] = (*arc)->str[i];
	t->str[i] = (*arc)->str[i];
	t->str[i + ((*arc)->str[i] == '\n')] = '\0';
	t->len += (i + ((*arc)->str[i] == '\n'));
	t->done += ((*arc)->str[i] == '\n');
	i += ((*arc)->str[i] == '\n');
	k = 0;
	while ((*arc)->str[i])
		(*arc)->str[k++] = (*arc)->str[i++];
	(*arc)->str[k] = '\0';
	ft_adjust_str(t);
	if ((*arc)->str[0])
		return ;
	ft_free_arc(arc);
}

char	*ft_get_next_line(int fd)
{
	static t_arc	*arc;
	t_track			t;

	if (BUFFER_SIZE <= 0 || fd < 0 || !ft_set_track(&t))
		return (NULL);
	if (ft_get_arc(&arc, fd))
		ft_arc_to_str(&t, &arc);
	while (!t.done)
	{
		t.read = read(fd, t.str + t.len, BUFFER_SIZE);
		if (t.read < 0 || (!t.read && !t.str[0]))
		{
			free(t.str);
			return (NULL);
		}
		if (!t.read)
			t.done = 1;
		t.str[t.len + t.read] = '\0';
		if (t.read > 0)
			ft_get_str(&t, &arc, fd);
	}
	ft_adjust_str(&t);
	return (t.str);
}

// RETURN:
// str "...\n\0" - if got a line
// NULL - if not got a line