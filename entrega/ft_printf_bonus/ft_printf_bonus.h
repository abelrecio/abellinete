/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:18:56 by abrecio-          #+#    #+#             */
/*   Updated: 2025/06/14 13:18:58 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_flags
{
	int		width;
	int		precision;
	int		dot;
	int		minus;
	int		zero;
	int		hash;
	int		plus;
	int		space;
	int		negative;
	char	spec;
}			t_flags;

int			ft_printf(const char *format, ...);
const char	*ft_parse_flags(const char *format, t_flags *flags, va_list args);
void		ft_init_flags(t_flags *flags);
int			ft_put_padding(char c, int width);
int			ft_handle_char(va_list args, t_flags flags);
int			ft_handle_string(va_list args, t_flags flags);
int			ft_handle_number(va_list args, t_flags flags, char spec);
char		*ft_itoa_base(unsigned long n, char *base, int base_len);
int			ft_get_prefix_len(unsigned long n, t_flags flags);
void		ft_add_prefix(char *str, unsigned long n, t_flags flags);
char		*ft_build_final_string(unsigned long n, char *num_str,
				t_flags flags);
char		*ft_format_number(unsigned long n, char *base, t_flags flags);
int			ft_putchar(char c);
int			ft_putstr(char *str);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);

#endif
