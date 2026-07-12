/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:10:27 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 15:06:43 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
int	ft_isascii(int c)
{
	if ((c >= 0) && (c <= 127))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isascii(65));
// 	printf("%d\n", ft_isascii(128));
// 	return (0);
// }
