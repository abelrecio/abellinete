/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:40:36 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 13:17:57 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_put_padding(char c, int width)
{
	int	count;

	count = 0;
	while (width > 0)
	{
		count += ft_putchar(c);
		width--;
	}
	return (count);
}

void	ft_init_flags(t_flags *flags)
{
	ft_memset(flags, 0, sizeof(t_flags));
	flags->precision = -1;
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}
