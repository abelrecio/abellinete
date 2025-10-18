/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_number_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:38:59 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 15:19:31 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

// PRECISION PADDING: Zeros needed to meet minimum digit requirement
// "%.5d", 42 → result[0] = 3 zeros → "00042"

// WIDTH PADDING: Zeros for field width when zero flag is active
// "%08d", 42 → result[1] = 6 zeros → "00000042"

// ZERO FLAG CONDITIONS: Only pad with zeros if no dot and no minus
// "%08.3d", 42 → result[1] = 3, result[0] = 1 → "0000042"

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

// STRING CONSTRUCTION: [PREFIX] + [WIDTH_ZEROS] + [PRECISION_ZEROS] + [NUMBER]
// "%#08.3x", 42 → "0x" + "00" + "0" + "2a" → "0x0002a"

// SEQUENTIAL ASSEMBLY: Add each component in correct order to result string
//ft_add_prefix() → memset(width_zeros)
// → memset(precision_zeros) → memcpy(number)

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
