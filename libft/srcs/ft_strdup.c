/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 16:06:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/05 16:04:23 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char			*res;
	int				i;
	unsigned int	size;

	i = -1;
	size = sizeof(*res) * (ft_strlen(s1) + 1);
	res = (char *)malloc(size);
	if (!res)
		return (0);
	while (s1[++i])
	{
		res[i] = s1[i];
	}
	res[i] = '\0';
	return (res);
}
