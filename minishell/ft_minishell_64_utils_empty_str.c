/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_64_utils_empty_str.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:37:31 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/04 14:49:04 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

//	RETURN:
//	-1	NULL
//	0	str exists and is NOT blanc
//	1	str is EMPTY
//	2	str is blanc of <space> and <tab> only
//	3	str is blanc of <space>, <tab> and <\n> only
int	ft_is_blanc_str(char *str)
{
	if (!str)
		return (-1);
	if (!*str)
		return (1);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (!*str)
		return (2);
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
		str++;
	if (!*str)
		return (3);
	return (0);
}
