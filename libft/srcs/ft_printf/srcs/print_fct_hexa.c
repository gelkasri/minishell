/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fct_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:44:57 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/07 12:08:27 by gel-kasr         ###   ########.fr       */
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
	unsigned int	i;
	char			*print;
	int				len;
	int				nb_space;
	int				nb_zero;

	i = va_arg(*ap, unsigned int);
	if (fmt.hh)
		i = (unsigned char)i;
	else if (fmt.h)
		i = (unsigned short)i;
	print = ft_ultoa_base((unsigned int)i, base);
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

int			print_hexa_uc(va_list *ap, t_fmt fmt)
{
	char *base;

	if (fmt.ll)
		return (print_hexa_uc_longlong(ap, fmt));
	else if (fmt.l)
		return (print_hexa_uc_long(ap, fmt));
	base = "0123456789ABCDEF";
	return (print_hexa_base(ap, fmt, base));
}

int			print_hexa_lc(va_list *ap, t_fmt fmt)
{
	char *base;

	if (fmt.ll)
		return (print_hexa_lc_longlong(ap, fmt));
	else if (fmt.l)
		return (print_hexa_lc_long(ap, fmt));
	base = "0123456789abcdef";
	return (print_hexa_base(ap, fmt, base));
}

int			print_adr(va_list *ap, t_fmt fmt)
{
	uintptr_t	adr;
	char		*print;
	int			len;

	adr = va_arg(*ap, uintptr_t);
	print = ft_ultoa_base(adr, "0123456789abcdef");
	len = ft_strlen(print) + 2;
	if (fmt.zero && fmt.min_width > len)
		ft_putnchar('0', fmt.min_width - len);
	else if (!fmt.minus && fmt.min_width > len)
		ft_putnchar(' ', fmt.min_width - len);
	ft_putstr("0x");
	ft_putstr(print);
	if (fmt.minus && fmt.min_width > len)
		ft_putnchar(' ', fmt.min_width - len);
	free(print);
	return ((fmt.min_width > len) ? fmt.min_width : len);
}
