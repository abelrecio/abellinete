/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clopez-b <clopez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:21:58 by clopez-b          #+#    #+#             */
/*   Updated: 2026/06/19 17:51:43 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*empty_substr(void)
{
	char	*sub;

	sub = malloc(1);
	if (!sub)
		return (NULL);
	sub[0] = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return (empty_substr());
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
