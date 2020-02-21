/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fct_hexa_l.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:44:57 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/07 12:08:15 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	sub_print_hexa(t_fmt fmt, int nb_space, int nb_zero, char *print)
{
	int len;

	len = ft_strlen(print);
	if (!fmt.minus && ((fmt.min_width > len && !fmt.zero) || nb_space))
		ft_putnchar(' ', nb_space);
	if (fmt.hash)
	{
		ft_putchar('0');
		ft_putchar(fmt.hash);
	}
	if ((fmt.zero && fmt.min_width > len) || fmt.precision)
	{
		ft_putnchar('0', nb_zero);
		ft_putstr(print);
	}
	else
		ft_putstr(print);
	if (fmt.minus && fmt.min_width > len + nb_zero)
		ft_putnchar(' ', fmt.min_width - len - nb_zero);
}

static int	print_hexa_base(va_list *ap, t_fmt fmt, char *base)
{
	unsigned long	i;
	char			*print;
	int				len;
	int				nb_space;
	int				nb_zero;

	i = va_arg(*ap, unsigned long);
	print = ft_ultoa_base((unsigned long)i, base);
	len = ft_strlen(print);
	nb_zero = (fmt.precision > len) ? fmt.precision - len : 0;
	fmt.min_width -= !!(fmt.hash && i) * 2;
	if (!fmt.point && fmt.zero)
		nb_zero = (fmt.min_width > len) ? fmt.min_width - len : 0;
	len += nb_zero;
	nb_space = (fmt.min_width > len) ? fmt.min_width - len : 0;
	fmt.hash = (fmt.hash && i) * (base[10] + 'x' - 'a');
	sub_print_hexa(fmt, nb_space, nb_zero, print);
	free(print);
	return (len + nb_space + 2 * !!(fmt.hash));
}

int			print_hexa_uc_long(va_list *ap, t_fmt fmt)
{
	char *base;

	base = "0123456789ABCDEF";
	return (print_hexa_base(ap, fmt, base));
}

int			print_hexa_lc_long(va_list *ap, t_fmt fmt)
{
	char *base;

	base = "0123456789abcdef";
	return (print_hexa_base(ap, fmt, base));
}
