/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:17:01 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 15:51:35 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
int	ft_isalnum(int c)
{
	if (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z'))
		|| ((c >= 'a') && (c <= 'z')))
		return (1);
	return (0);
}

// int main(void)
// {
// 	int	c;

// 	c = 'A';
// 	if (ft_isalnum(c))
// 		printf("%c is alphanumeric\n", c);
// 	else
// 		printf("%c is not alphanumeric\n", c);
// 	return (0);
// }