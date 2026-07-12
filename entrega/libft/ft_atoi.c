/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:26:32 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 17:16:16 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' '
		|| *str == '\t'
		|| *str == '\n'
		|| *str == '\r'
		|| *str == '\f'
		|| *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

// int	main(void)
// {
// 	printf("%d\n", ft_atoi("37"));
// 	printf("%d\n", ft_atoi(" --459m3"));
// 	printf("%d\n", ft_atoi(" -45m3"));
// 	return (0);
// }
