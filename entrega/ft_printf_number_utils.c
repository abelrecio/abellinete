/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:57:58 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/24 23:57:59 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_calculate_num_len(unsigned long n, int base_len)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(unsigned long n, char *base, int base_len)
{
	char	*str;
	int		len;
	int		i;

	len = ft_calculate_num_len(n, base_len);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = base[0];
		return (str);
	}
	i = len - 1;
	while (i >= 0)
	{
		str[i] = base[n % base_len];
		n /= base_len;
		i--;
	}
	return (str);
}
