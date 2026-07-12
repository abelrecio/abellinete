/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:17:45 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 15:09:09 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isdigit(48));
// 	printf("%d\n", ft_isdigit(57));
// 	return (0);
// }
