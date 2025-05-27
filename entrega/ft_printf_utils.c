/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:58:16 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/24 23:58:22 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
