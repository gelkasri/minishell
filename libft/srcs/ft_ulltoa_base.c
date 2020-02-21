/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:15:08 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/17 02:27:55 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_ulltoa_base(unsigned long long n, char *base)
{
	char				*res;
	int					size;
	unsigned long long	n1;

	size = 1;
	n1 = n;
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
	return (res);
}
