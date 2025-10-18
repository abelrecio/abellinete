/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:41:35 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/09 19:41:37 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		i += ft_putchar(str[i]);
	return (i);
}

int	ft_putnbr_base(unsigned long n, char *base, int base_len)
{
	int	count;

	count = 0;
	if (n >= (unsigned long)base_len)
		count += ft_putnbr_base(n / base_len, base, base_len);
	count += ft_putchar(base[n % base_len]);
	return (count);
}

int	ft_putnbr(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	count += ft_putnbr_base(n, "0123456789", 10);
	return (count);
}

int	ft_format_ptr(va_list args)
{
	int				count;
	unsigned long	ptr;

	ptr = va_arg(args, unsigned long);
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	count = ft_putstr("0x");
	count += ft_putnbr_base(ptr, "0123456789abcdef", 16);
	return (count);
}
