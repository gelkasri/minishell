/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:33:46 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/05 11:17:04 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*dst_s;
	char	*src_s;

	if (!dst && !src)
		return (NULL);
	dst_s = (char *)dst;
	src_s = (char *)src;
	i = -1;
	if (src_s > dst_s)
	{
		while (++i < (int)len)
			dst_s[i] = src_s[i];
	}
	else
	{
		len--;
		while ((int)len >= 0)
		{
			dst_s[len] = src_s[len];
			len--;
		}
	}
	return (dst);
}
