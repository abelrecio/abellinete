/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:06:31 by abrecio-          #+#    #+#             */
/*   Updated: 2025/05/25 03:06:51 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_calculate_padding(int num_len, int prefix_len, t_flags flags,
		int *result)
{
	result[0] = 0;
	result[1] = 0;
	if (flags.precision > num_len)
		result[0] = flags.precision - num_len;
	if (flags.zero && !flags.dot && !flags.minus)
	{
		result[1] = flags.width - (prefix_len + result[0] + num_len);
		if (result[1] < 0)
			result[1] = 0;
	}
}

char	*ft_build_final_string(unsigned long n, char *num_str, t_flags flags)
{
	char	*result;
	int		num_len;
	int		prefix_len;
	int		padding[2];

	num_len = 0;
	if (num_str)
		num_len = ft_strlen(num_str);
	prefix_len = ft_get_prefix_len(n, flags);
	ft_calculate_padding(num_len, prefix_len, flags, padding);
	result = (char *)ft_calloc(prefix_len + padding[0] + padding[1] + num_len
			+ 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_add_prefix(result, n, flags);
	if (padding[1] > 0)
		ft_memset(result + prefix_len, '0', padding[1]);
	if (padding[0] > 0)
		ft_memset(result + prefix_len + padding[1], '0', padding[0]);
	if (num_str)
		ft_memcpy(result + prefix_len + padding[1] + padding[0], num_str,
			num_len);
	return (result);
}

char	*ft_format_number(unsigned long n, char *base, t_flags flags)
{
	char	*num_str;
	char	*result;

	num_str = NULL;
	if (n != 0 || (flags.precision != 0 || !flags.dot))
		num_str = ft_itoa_base(n, base, ft_strlen(base));
	if (n != 0 && !num_str)
		return (NULL);
	result = ft_build_final_string(n, num_str, flags);
	if (num_str)
		free(num_str);
	return (result);
}
