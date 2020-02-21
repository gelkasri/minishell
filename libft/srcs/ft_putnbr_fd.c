/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:36:02 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/04 13:36:07 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(long long n, int fd)
{
	unsigned long long u;

	u = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u = -n;
	}
	if (u <= 9)
	{
		ft_putchar_fd(u + '0', fd);
	}
	else
	{
		ft_putnbr_fd(u / 10, fd);
		ft_putchar_fd((u % 10) + '0', fd);
	}
}
