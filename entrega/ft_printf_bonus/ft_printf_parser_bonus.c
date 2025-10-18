/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:39:57 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 15:13:22 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

// MINUS FLAG: Left-align output in field width
// "%-5d" with 42 → "42   " | "%-8s" with "hi" → "hi      "

// ZERO FLAG: Pad with zeros instead of spaces  
// %05d" with 42 → "00042" | "%08x" with 255 → "000000ff"

// DOT FLAG: Start precision specification
// "%.4d" with 42 → "0042" | "%.2s" with "hello" → "he"

// HASH FLAG: Add prefix for hex/octal formats
// "%#x" with 255 → "0xff" | "%#o" with 8 → "010"

// PLUS FLAG: Always show sign for numbers
// "%+d" with 42 → "+42" | "%+d" with -5 → "-5"

// SPACE FLAG: Add space before positive numbers
// "% d" with 42 → " 42" | "% d" with -5 → "-5"

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

// WIDTH ASTERISK: Get width value from argument list
// "%*d", 5, 42 → "   42" | "%*s", 10, "hi" → "        hi"

// NEGATIVE WIDTH: Convert to positive width + left-align flag
// "%*d", -5, 42 → "42   " | "%*s", -8, "hi" → "hi      "

// PRECISION ASTERISK: Get precision value from argument list (after dot)
// "%.*d", 4, 42 → "0042" | "%.*s", 3, "hello" → "hel"

// ASTERISK DISPATCHER: Route to width or precision based on dot flag
// "%*.*s", 8, 3, "hello" → "     hel" | "%*d", 6, 42 → "    42"

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

// PRECISION DIGITS: Build precision value digit by digit (after dot)
// "%.4d", 42 → precision builds as 4 → "0042"

// WIDTH DIGITS: Build width value digit by digit (before dot)  
// "%8d", 42 → width builds as 8 → "      42"

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
