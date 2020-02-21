/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_del_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:20:15 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/05 18:30:05 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_str_del_char(char const *s1, char const *set)
{
	unsigned int	size;
	unsigned int	i;
	char			*res;

	if (!set || set[0] == 0)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	size = 0;
	i = -1;
	while (++i < ft_strlen(s1))
		if (!ft_strchr(set, s1[i]))
			size++;
	res = (char *)malloc(sizeof(*res) * (size + 1));
	size = -1;
	i = 0;
	while (++size < ft_strlen(s1))
	{
		if (!ft_strchr(set, s1[size]))
		{
			res[i] = s1[size];
			i++;
		}
	}
	return (res);
}
