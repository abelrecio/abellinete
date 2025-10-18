/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:38:43 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 13:16:59 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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
