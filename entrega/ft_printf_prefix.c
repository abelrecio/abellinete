/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:58:05 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/24 23:58:07 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_prefix_len(unsigned long n, t_flags flags)
{
	int	len;

	len = 0;
	if (flags.spec == 'd' || flags.spec == 'i')
	{
		if (flags.negative || flags.plus || flags.space)
			len = 1;
	}
	if (flags.hash && n != 0)
	{
		if (flags.spec == 'x' || flags.spec == 'X' || flags.spec == 'p')
			len += 2;
	}
	return (len);
}

void	ft_add_prefix(char *str, unsigned long n, t_flags flags)
{
	int	i;

	i = 0;
	if (flags.spec == 'd' || flags.spec == 'i')
	{
		if (flags.negative)
			str[i++] = '-';
		else if (flags.plus)
			str[i++] = '+';
		else if (flags.space)
			str[i++] = ' ';
	}
	if (flags.hash && n != 0)
	{
		if (flags.spec == 'x' || flags.spec == 'p')
		{
			str[i++] = '0';
			str[i] = 'x';
		}
		else if (flags.spec == 'X')
		{
			str[i++] = '0';
			str[i] = 'X';
		}
	}
}
