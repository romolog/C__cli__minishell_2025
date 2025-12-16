/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:28:53 by rponomar          #+#    #+#             */
/*   Updated: 2024/10/23 19:40:29 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_counter(char const *s, char c)
{
	char	*str;
	size_t	counter;

	str = (char *)s;
	counter = 0;
	if (!*s)
		return (0);
	if (c == 0)
		return (1);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			counter++;
		else
			return (counter);
		while (*str && *str != c)
			str++;
	}
	return (counter);
}

static void	*ft_free_2d_arr(char **arr, size_t elements)
{
	while (elements)
		free(arr[--elements]);
	free(arr);
	return (NULL);
}

static char	**ft_get_str(char *str)
{
	char	**arr;
	size_t	len;

	len = ft_strlen(str);
	arr = malloc(sizeof(char *) * 2);
	if (arr == NULL)
		return (NULL);
	arr[0] = malloc(len + 1);
	if (!arr[0] && ft_free_2d_arr(arr, 0))
		return (NULL);
	arr[1] = NULL;
	ft_strlcpy(arr[0], str, len + 1);
	return (arr);
}

static char	**ft_get_words(char *src, char dlmtr, char **dst_arr, size_t words)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < words)
	{
		len = 0;
		while (*src == dlmtr)
			src++;
		while (*(src + len) != dlmtr && *(src + len))
			len++;
		dst_arr[i] = malloc(len + 1);
		if (!dst_arr[i])
			return (ft_free_2d_arr(dst_arr, i));
		ft_strlcpy(dst_arr[i], src, len + 1);
		src += len;
		i++;
	}
	dst_arr[words] = NULL;
	return (dst_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**dst_arr;
	size_t	words;

	if (c == '\0' && *s)
		return (ft_get_str((char *)s));
	words = ft_word_counter(s, c);
	dst_arr = malloc((words + 1) * sizeof(char *));
	if (!dst_arr)
		return (NULL);
	return (ft_get_words((char *)s, c, dst_arr, words));
}

// gets a string and delimiter
// returns arr[x][str] of words 0-terminated
//
// #include <stdio.h>
// int main()
// {
// 	//char str[] = "  ab ";
// 	//char d = ' ';
// 	printf("hello\n");
// 	char ** tab = ft_split("\0aa\0bbb", '\0');
// 	printf("%s\n%s\n", tab[0], tab[1]);
// 	return (0);
// }