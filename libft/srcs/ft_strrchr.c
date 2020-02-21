/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:04:01 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/10 11:34:26 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s) - 1;
	if (i < 0 && c)
		return (NULL);
	if (c == 0)
		return ((char *)(s + ft_strlen((char*)s)));
	while (i >= 0 && s[i] != (unsigned char)c)
		i--;
	if (i < 0)
		return (NULL);
	return ((char *)(s + i));
}
