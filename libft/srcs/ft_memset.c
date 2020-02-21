/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:33:12 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/04 13:41:34 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)b;
	while (i < (int)len)
	{
		res[i] = (unsigned char)c;
		i++;
	}
	return ((void *)b);
}
