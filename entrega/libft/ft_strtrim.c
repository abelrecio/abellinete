/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clopez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:26:22 by clopez-b          #+#    #+#             */
/*   Updated: 2026/06/19 17:26:25 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_set(s1[start], set))
		start++;
	end = 0;
	while (s1[end])
		end++;
	while (end > start && is_set(s1[end - 1], set))
		end--;
	len = end - start;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
		res[len] = s1[start + len];
	return (res);
}
