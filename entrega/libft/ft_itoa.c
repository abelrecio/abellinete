/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:28:17 by clopez-b          #+#    #+#             */
/*   Updated: 2026/05/18 15:15:49 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <stdlib.h>

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_fill_str(char *str, long nb, int len)
{
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[len] = (char)('0' + nb % 10);
		nb /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;
	long	nb;

	nb = (long)n;
	neg = 0;
	if (nb < 0)
	{
		neg = 1;
		nb = -nb;
	}
	len = ft_numlen(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	ft_fill_str(str, nb, len);
	if (neg)
		str[0] = '-';
	return (str);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(65));
// 	printf("%s\n", ft_itoa(-128));
// 	return (0);
// }