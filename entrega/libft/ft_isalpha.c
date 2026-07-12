/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:18:36 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 15:51:35 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
int	ft_isalpha(int c)
{
	if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
		return (1);
	return (0);
}

// int main(void)
// {
// 	int	c;

// 	c = '9';
// 	if (ft_isalpha(c))
// 		printf("%c is an alphabetic character\n", c);
// 	else
// 		printf("%c is not an alphabetic character\n", c);
// 	return (0);
// }