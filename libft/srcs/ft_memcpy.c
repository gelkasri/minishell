/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:33:02 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/07 00:35:32 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*dst_s;
	char	*src_s;

	if (!dst && !src)
		return (NULL);
	dst_s = (char *)dst;
	src_s = (char *)src;
	i = 0;
	while (i < (int)n)
	{
		dst_s[i] = src_s[i];
		i++;
	}
	return (dst);
}
