/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:41:25 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/09 19:41:27 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(va_list args, char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (format == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		count = ft_format_ptr(args);
	else if (format == 'd' || format == 'i')
		count = ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		count = ft_putnbr_base(va_arg(args, unsigned int), "0123456789", 10);
	else if (format == 'x')
		count = ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef",
				16);
	else if (format == 'X')
		count = ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF",
				16);
	else if (format == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!format)
		return (-1);
	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_format(args, format[i + 1]);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
