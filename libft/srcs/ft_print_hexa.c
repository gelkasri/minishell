/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:16:12 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/04 17:17:57 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_hexa(unsigned char i)
{
	int					div;
	int					mod;
	unsigned char		p;
	char				bs;

	div = i / 16;
	mod = i % 16;
	bs = '\\';
	write(1, &bs, 1);
	if (div <= 9)
		p = '0' + div;
	else
		p = div - 10 + 'a';
	write(1, &p, 1);
	if (mod <= 9)
		p = '0' + mod;
	else
		p = mod - 10 + 'a';
	write(1, &p, 1);
}
