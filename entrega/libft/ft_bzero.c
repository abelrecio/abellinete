/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:26:32 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 17:09:47 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stddef.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

// int	main(void)
// {
// 	char	str[50] = "Hello, World!";
// 	size_t	n = 5;

// 	printf("Before ft_bzero: %s\n", str);
// 	ft_bzero(str, n);
// 	printf("After ft_bzero: %s\n", str);

// 	return (0);
// }