/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:22:25 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/28 20:19:07 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_match_set(char target, char const *ch_set)
{
	char	*set;

	set = (char *)ch_set;
	while (*set)
	{
		if (*set == target)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*ptr;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = (char *)s1;
	while (ft_is_match_set(*start, set))
		start++;
	len = ft_strlen(start);
	while (len && ft_is_match_set(*(start + len - 1), set))
		len--;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	while (len--)
		ptr[len] = start[len];
	return (ptr);
}
