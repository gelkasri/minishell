/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 03:03:37 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/04 20:47:04 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	unsigned int	n;
	int				i;

	n = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[n])
	{
		i = -1;
		while ((unsigned int)++i < ft_strlen(needle))
		{
			if (needle[i] != haystack[n + i])
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
