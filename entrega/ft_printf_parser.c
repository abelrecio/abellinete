/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:58:02 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/25 03:06:16 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_handle_flag_char(char c, t_flags *flags)
{
	if (c == '-')
		flags->minus = 1;
	else if (c == '0' && !flags->minus && !flags->dot)
		flags->zero = 1;
	else if (c == '.')
	{
		flags->dot = 1;
		flags->precision = 0;
	}
	else if (c == '#')
		flags->hash = 1;
	else if (c == '+')
		flags->plus = 1;
	else if (c == ' ')
		flags->space = 1;
}

static void	ft_handle_width_asterisk(va_list args, t_flags *flags)
{
	flags->width = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->minus = 1;
		flags->width = -flags->width;
	}
}

static void	ft_handle_asterisk(va_list args, t_flags *flags)
{
	if (flags->dot)
		flags->precision = va_arg(args, int);
	else
		ft_handle_width_asterisk(args, flags);
}

static void	ft_handle_digit(char c, t_flags *flags)
{
	if (flags->dot)
		flags->precision = (flags->precision * 10) + (c - '0');
	else
		flags->width = (flags->width * 10) + (c - '0');
}

const char	*ft_parse_flags(const char *format, t_flags *flags, va_list args)
{
	ft_init_flags(flags);
	while (*format && ft_strchr("-0.# +*123456789", *format))
	{
		if (*format == '*')
			ft_handle_asterisk(args, flags);
		else if (*format == '0' && flags->width == 0 && !flags->dot)
			ft_handle_flag_char(*format, flags);
		else if (*format >= '0' && *format <= '9')
			ft_handle_digit(*format, flags);
		else
			ft_handle_flag_char(*format, flags);
		format++;
	}
	if (flags->minus || flags->dot)
		flags->zero = 0;
	return (format);
}
