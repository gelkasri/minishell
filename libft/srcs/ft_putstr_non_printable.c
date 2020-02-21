/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 03:19:26 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/04 17:25:23 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr_non_printable(char *str)
{
	unsigned int	i;
	unsigned char	c;

	i = 0;
	c = str[0];
	while (str[i])
	{
		c = str[i];
		if (c >= 32 && c <= 126)
			ft_putchar(c);
		else
			ft_print_hexa((unsigned char)c);
		i++;
	}
}
