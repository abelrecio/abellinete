/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 00:36:44 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/25 00:36:45 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_null_pointer(t_flags flags)
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
