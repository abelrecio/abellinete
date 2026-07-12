/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:01:31 by claudialbom       #+#    #+#             */
/*   Updated: 2026/05/18 15:09:11 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(const char *big, const char *little, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && (i < len))
	{
		j = 0;
		while (big[i + j] && little[j] && (big[i + j] == little[j])
			&& (i + j < len))
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
// int	main(void)
// {
// 	printf("ft_strnstr: prueba rápida\n");
// 	return (0);
// }
