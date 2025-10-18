/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:39:11 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 13:17:18 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_handle_specifier(va_list args, t_flags flags, char spec)
{
	if (spec == 'c')
		return (ft_handle_char(args, flags));
	else if (spec == 's')
		return (ft_handle_string(args, flags));
	else if (spec == 'd' || spec == 'i' || spec == 'u' || spec == 'x'
		|| spec == 'X' || spec == 'p' || spec == 'o')
		return (ft_handle_number(args, flags, spec));
	else if (spec == '%')
		return (ft_putchar('%'));
	return (0);
}

static const char	*ft_format(va_list args, const char *format, int *count)
{
	t_flags	flags;
	char	spec;
	int		result;

	format = ft_parse_flags(format, &flags, args);
	if (!*format)
		return (format);
	spec = *format;
	format++;
	result = ft_handle_specifier(args, flags, spec);
	*count += result;
	return (format);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			format = ft_format(args, format, &count);
		}
		else
		{
			count += ft_putchar(*format);
			format++;
		}
	}
	va_end(args);
	return (count);
}
