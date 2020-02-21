/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 04:08:39 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/16 05:16:36 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa_base(int n, char *base)
{
	char			*res;
	int				size;
	unsigned int	n1;
	int				s;

	s = n;
	size = (n < 0) ? 2 : 1;
	n1 = (n < 0) ? -n : n;
	while (n /= ft_strlen(base))
		size++;
	if (!(res = ft_memalloc(size + 1)))
		return (NULL);
	res[size--] = 0;
	if (!n1)
	{
		res[size] = '0';
		return (res);
	}
	while (n1 && (res[size--] = base[n1 % ft_strlen(base)]))
		n1 /= ft_strlen(base);
	if (s < 0)
		res[size] = '-';
	return (res);
}
