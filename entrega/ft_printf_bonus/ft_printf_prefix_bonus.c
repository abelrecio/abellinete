/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prefix_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:40:15 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 13:17:44 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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
		else if (flags.spec == 'o')
			len += 1;
	}
	return (len);
}

static char	*ft_add_spec(char *str, t_flags flags)
{
	if (flags.spec == 'd' || flags.spec == 'i')
	{
		if (flags.negative)
			*str++ = '-';
		else if (flags.plus)
			*str++ = '+';
		else if (flags.space)
			*str++ = ' ';
	}
	return (str);
}

static char	*ft_add_hex(char *str, unsigned long n, t_flags flags)
{
	if (flags.hash && n != 0)
	{
		if (flags.spec == 'x' || flags.spec == 'p')
		{
			*str++ = '0';
			*str++ = 'x';
		}
		else if (flags.spec == 'X')
		{
			*str++ = '0';
			*str++ = 'X';
		}
		else if (flags.spec == 'o')
			*str++ = '0';
	}
	return (str);
}

void	ft_add_prefix(char *str, unsigned long n, t_flags flags)
{
	str = ft_add_spec(str, flags);
	str = ft_add_hex(str, n, flags);
}
