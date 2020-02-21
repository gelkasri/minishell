/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:01:30 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/08 15:47:27 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			ft_intlen(long long i)
{
	int		res;
	char	*nbr;

	nbr = ft_lltoa(i);
	res = ft_strlen(nbr);
	free(nbr);
	return (res);
}

int			ft_uintlen(unsigned long long i)
{
	int		res;
	char	*nbr;

	nbr = ft_ulltoa_base(i, "0123456789");
	res = ft_strlen(nbr);
	free(nbr);
	return (res);
}

void		flags_cut(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_index("123456789", str[i]) >= 0)
			str[i] = 0;
		i++;
	}
}
