/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:39:58 by rponomar          #+#    #+#             */
/*   Updated: 2024/08/25 14:53:26 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (512);
	else
		return (0);
}

static int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (256);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if (ft_isupper(c) || ft_islower(c))
		return (1024);
	else
		return (0);
}
