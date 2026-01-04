/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:13:22 by rponomar          #+#    #+#             */
/*   Updated: 2024/11/10 17:26:04 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETLINE_H
# define FT_GETLINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_track
{
	int		done;
	char	*str;
	size_t	len;
	ssize_t	read;
}	t_track;

typedef struct s_arc
{
	int				fd;
	int				start;
	char			*str;
	struct s_arc	*next;
	struct s_arc	*prev;
}	t_arc;

char	*ft_get_next_line(int fd);
void	ft_adjust_str(t_track *t);
void	ft_get_str(t_track *t, t_arc **arc, int fd);
void	ft_free_arc(t_arc **arc);

#endif
