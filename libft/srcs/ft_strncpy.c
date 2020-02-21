/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 01:27:25 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/06 19:43:41 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < (unsigned int)len)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < (unsigned int)len)
		dest[i++] = '\0';
	return (dest);
}
