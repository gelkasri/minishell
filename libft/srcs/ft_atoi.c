/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:20:11 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/08 04:15:56 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_atoi(const char *str)
{
	unsigned long	res;
	int				len;
	int				i;
	int				s;

	len = ft_strlen(str) - 1;
	res = 0;
	i = 0;
	while (ft_isspace(str[i]) && i < len)
		i++;
	s = (str[i] == '-') ? -1 : 1;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (i <= len && ft_isdigit(str[i]))
	{
		if (res * 10 < res)
			return ((s > 0) ? -1 : 0);
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return ((unsigned long)(s * res));
}
