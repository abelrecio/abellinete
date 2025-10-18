/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:39:22 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 13:17:24 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_handle_null_pointer(t_flags flags)
{
	int	count;

	count = 0;
	if (flags.width > 5)
	{
		if (flags.minus)
		{
			count += ft_putstr("(nil)");
			count += ft_put_padding(' ', flags.width - 5);
		}
		else
		{
			count += ft_put_padding(' ', flags.width - 5);
			count += ft_putstr("(nil)");
		}
	}
	else
		count += ft_putstr("(nil)");
	return (count);
}

static long	ft_get_number(va_list args, t_flags *flags, char spec)
{
	long	n;

	if (spec == 'd' || spec == 'i')
	{
		n = va_arg(args, int);
		if (n < 0)
		{
			flags->negative = 1;
			n = -n;
		}
	}
	else if (spec == 'u' || spec == 'x' || spec == 'X' || spec == 'o')
		n = (unsigned int)va_arg(args, int);
	else if (spec == 'p')
	{
		n = (unsigned long)va_arg(args, void *);
		flags->hash = 1;
	}
	else
		n = 0;
	return (n);
}

static char	*ft_get_base(char spec)
{
	if (spec == 'd' || spec == 'i' || spec == 'u')
		return ("0123456789");
	if (spec == 'x' || spec == 'p')
		return ("0123456789abcdef");
	if (spec == 'X')
		return ("0123456789ABCDEF");
	if (spec == 'o')
		return ("01234567");
	return ("0123456789");
}

static int	ft_print_number(char *str, t_flags flags)
{
	int		count;
	int		len;
	char	pad_char;

	count = 0;
	len = ft_strlen(str);
	pad_char = ' ';
	if (flags.zero && !flags.dot && !flags.minus)
		pad_char = '0';
	if (flags.minus)
	{
		count += ft_putstr(str);
		count += ft_put_padding(' ', flags.width - len);
	}
	else
	{
		if (flags.width > len)
			count += ft_put_padding(pad_char, flags.width - len);
		count += ft_putstr(str);
	}
	return (count);
}

int	ft_handle_number(va_list args, t_flags flags, char spec)
{
	long	n;
	char	*str;
	char	*base;
	int		count;

	flags.spec = spec;
	flags.negative = 0;
	base = ft_get_base(spec);
	n = ft_get_number(args, &flags, spec);
	if (spec == 'p' && n == 0)
		return (ft_handle_null_pointer(flags));
	str = ft_format_number(n, base, flags);
	if (!str)
		return (0);
	count = ft_print_number(str, flags);
	free(str);
	return (count);
}
