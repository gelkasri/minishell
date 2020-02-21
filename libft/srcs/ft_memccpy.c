/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:32:54 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/07 23:06:40 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dst_s;
	unsigned char	*src_s;

	dst_s = (unsigned char *)dst;
	src_s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == src_s[i])
		{
			dst_s[i] = src_s[i];
			return ((void *)dst_s + i + 1);
		}
		dst_s[i] = src_s[i];
		i++;
	}
	return (NULL);
}
