/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:37:17 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/04 20:55:42 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	n;
	int				i;

	n = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[n] && n < len)
	{
		i = -1;
		while ((unsigned int)++i < ft_strlen(needle))
		{
			if (needle[i] != haystack[n + i] || (unsigned int)(n + i) > len - 1)
				break ;
			else
				continue;
		}
		if ((unsigned int)i == ft_strlen(needle))
			return ((char *)(haystack + n));
		n++;
	}
	return (NULL);
}
