/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:58:11 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/25 02:09:01 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_handle_null_str(int precision)
{
	if (precision >= 0 && precision < 6)
		return ("");
	return ("(null)");
}

static int	ft_print_content(char *str, int precision)
{
	int	count;

	count = 0;
	if (precision != 0)
	{
		while (*str && (precision < 0 || count < precision))
		{
			count += ft_putchar(*str);
			str++;
		}
	}
	return (count);
}

static int	ft_apply_padding(int width, int len, char c)
{
	if (width > len)
		return (ft_put_padding(c, width - len));
	return (0);
}

static char	ft_get_pad_char(t_flags flags)
{
	if (flags.zero && !flags.dot && !flags.minus)
		return ('0');
	return (' ');
}

int	ft_handle_string(va_list args, t_flags flags)
{
	char	*str;
	int		len;
	int		count;

	str = va_arg(args, char *);
	if (!str)
		str = ft_handle_null_str(flags.precision);
	len = ft_strlen(str);
	if (flags.precision >= 0 && flags.precision < len)
		len = flags.precision;
	count = 0;
	if (flags.minus)
	{
		count += ft_print_content(str, flags.precision);
		count += ft_apply_padding(flags.width, len, ' ');
	}
	else
	{
		count += ft_apply_padding(flags.width, len, ft_get_pad_char(flags));
		count += ft_print_content(str, flags.precision);
	}
	return (count);
}
