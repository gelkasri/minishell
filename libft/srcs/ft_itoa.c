/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:32:02 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/08 05:13:11 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa(int n)
{
	char			*res;
	int				size;
	unsigned int	n1;
	int				s;

	s = n;
	size = (n < 0) ? 2 : 1;
	n1 = (n < 0) ? -n : n;
	while (n /= 10)
		size++;
	if (!(res = ft_memalloc(size + 1)))
		return (NULL);
	res[size--] = 0;
	if (!n1)
	{
		res[size] = '0';
		return (res);
	}
	while (n1 && (res[size--] = n1 % 10 + '0'))
		n1 /= 10;
	if (s < 0)
		res[size] = '-';
	return (res);
}
