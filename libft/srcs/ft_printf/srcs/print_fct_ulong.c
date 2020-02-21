/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fct_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 04:49:28 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/08 15:56:10 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	ft_putunbr(unsigned long long n)
{
	unsigned long long u;

	u = n;
	if (n < 0)
	{
		ft_putchar('-');
		u = -n;
	}
	if (u <= 9)
	{
		ft_putchar(u + '0');
	}
	else
	{
		ft_putnbr(u / 10);
		ft_putchar((u % 10) + '0');
	}
}

static void	sub_long(unsigned long i, t_fmt fmt, int nb_space, int nb_zero)
{
	int len;

	len = ft_intlen(i) + ((fmt.plus || fmt.space) && i >= 0);
	if (!fmt.minus && ((fmt.min_width > len && !fmt.zero) || nb_space))
		ft_putnchar(' ', nb_space);
	if ((fmt.plus || fmt.space) && i >= 0)
		ft_putchar((fmt.plus) ? '+' : ' ');
	if ((fmt.zero && fmt.min_width > len) || fmt.precision)
	{
		ft_putnchar('-', (i < 0) ? 1 : 0);
		ft_putnchar('0', nb_zero);
		ft_putunbr((i < 0) ? -i : i);
	}
	else
		ft_putunbr(i);
	if (fmt.minus && fmt.min_width > len)
		ft_putnchar(' ', nb_space);
}

int			print_ulong(va_list *ap, t_fmt fmt)
{
	unsigned long	i;
	int				len;
	int				nb_space;
	int				nb_zero;

	i = va_arg(*ap, unsigned long);
	len = ft_uintlen(i) + ((fmt.plus || fmt.space) && i >= 0);
	nb_zero = (fmt.precision + ((i < 0) || ((fmt.plus || fmt.space) &&
		i >= 0)) > len) ? fmt.precision - len + ((i < 0) || ((fmt.plus
		|| fmt.space) && i >= 0)) : 0;
	if (!fmt.point && fmt.zero)
		nb_zero = (fmt.min_width > len) ? fmt.min_width - len : 0;
	len += nb_zero;
	nb_space = (fmt.min_width > len) ?
		fmt.min_width - len : 0;
	sub_long(i, fmt, nb_space, nb_zero);
	return (len + nb_space);
}
