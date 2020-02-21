/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 08:40:31 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/10 11:22:41 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	s;
	unsigned int	d;
	unsigned int	d0;
	unsigned int	res;
	unsigned int	size;

	s = 0;
	d = ft_strlen(dst);
	d0 = d;
	size = (unsigned int)dstsize;
	if (!size)
		return (ft_strlen(src));
	res = (size > d) ? d + ft_strlen(src) : size + ft_strlen(src);
	while (src[s] && d < (size - 1))
		dst[d++] = src[s++];
	if (d0 <= dstsize)
		dst[d] = '\0';
	return (res);
}
