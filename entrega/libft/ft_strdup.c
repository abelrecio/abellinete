/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clopez-b <clopez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:04:06 by claudialbom       #+#    #+#             */
/*   Updated: 2026/06/19 16:56:54 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	copy = (char *)malloc((i + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

// int	main(void)
// {
// 	printf("ft_strdup: prueba rápida\n");
// 	return (0);
// } 
