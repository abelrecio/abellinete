/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:08:45 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 15:05:32 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
int	ft_isprint(int c)
{
	if ((c >= 32) && (c <= 126))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isprint(32));
// 	printf("%d\n", ft_isprint(126));
// 	return (0);
// }
