/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:57:34 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/24 23:57:35 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_char(va_list args, t_flags flags)
{
	int		count;
	char	c;

	c = (char)va_arg(args, int);
	count = 0;
	if (flags.minus)
	{
		count += ft_putchar(c);
		if (flags.width > 1)
			count += ft_put_padding(' ', flags.width - 1);
	}
	else
	{
		if (flags.width > 1)
			count += ft_put_padding(' ', flags.width - 1);
		count += ft_putchar(c);
	}
	return (count);
}
