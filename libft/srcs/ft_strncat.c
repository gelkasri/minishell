/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 05:09:28 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/04 19:24:47 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int	s;
	unsigned int	d;
	unsigned int	nb;

	s = 0;
	d = 0;
	nb = (unsigned int)n;
	while (s1[d])
		d++;
	while (s2[s] && s < nb)
	{
		s1[d] = s2[s];
		d++;
		s++;
	}
	s1[d] = '\0';
	return (s1);
}
