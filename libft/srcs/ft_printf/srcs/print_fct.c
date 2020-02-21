/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 04:49:28 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/09 19:51:23 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			print_perc(va_list *ap, t_fmt fmt)
{
	(void)ap;
	if (fmt.zero && fmt.min_width)
		ft_putnchar('0', fmt.min_width - 1);
	else if (!fmt.minus && fmt.min_width)
		ft_putnchar(' ', fmt.min_width - 1);
	ft_putchar('%');
	if (fmt.minus && fmt.min_width)
		ft_putnchar(' ', fmt.min_width - 1);
	return ((fmt.min_width > 1) ? fmt.min_width : 1);
}

int			print_char(va_list *ap, t_fmt fmt)
{
	int	c;

	if (fmt.zero && fmt.min_width)
		ft_putnchar('0', fmt.min_width - 1);
	else if (!fmt.minus && fmt.min_width)
		ft_putnchar(' ', fmt.min_width - 1);
	c = va_arg(*ap, int);
	ft_putchar(c);
	if (fmt.minus && fmt.min_width)
		ft_putnchar(' ', fmt.min_width - 1);
	return ((fmt.min_width > 1) ? fmt.min_width : 1);
}

int			print_str(va_list *ap, t_fmt fmt)
{
	char	*str;
	char	*str2;
	int		len;

	str2 = va_arg(*ap, char *);
	if (!str2)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str2);
	if ((fmt.precision < (int)ft_strlen(str)) && fmt.point)
		str[fmt.precision] = 0;
	len = ft_strlen(str);
	if (fmt.zero && fmt.min_width > len)
		ft_putnchar('0', fmt.min_width - len);
	else if (!fmt.minus && fmt.min_width > len)
		ft_putnchar(' ', fmt.min_width - len);
	ft_putstr(str);
	if (fmt.minus && fmt.min_width > len)
		ft_putnchar(' ', fmt.min_width - len);
	free(str);
	return ((fmt.min_width > len) ? fmt.min_width : len);
}

static void	sub_print_int(int i, t_fmt fmt, int nb_space, int nb_zero)
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
		ft_putnbr((i < 0) ? -i : i);
	}
	else if (i || !fmt.point)
		ft_putnbr(i);
	if (fmt.minus && fmt.min_width > len)
		ft_putnchar(' ', nb_space);
}

int			print_int(va_list *ap, t_fmt fmt)
{
	int		i;
	int		len;
	int		nb_space;
	int		nb_zero;

	if (fmt.ll)
		return (print_longlong(ap, fmt));
	else if (fmt.l)
		return (print_long(ap, fmt));
	i = va_arg(*ap, int);
	if (fmt.hh)
		i = (char)i;
	else if (fmt.h)
		i = (short)i;
	len = ft_intlen(i) + ((fmt.plus || fmt.space) && i >= 0);
	nb_zero = (fmt.precision + ((i < 0) || ((fmt.plus || fmt.space) &&
		i >= 0)) > len) ? fmt.precision - len + ((i < 0) || ((fmt.plus
		|| fmt.space) && i >= 0)) : 0;
	if (!fmt.point && fmt.zero)
		nb_zero = (fmt.min_width > len) ? fmt.min_width - len : 0;
	len += nb_zero;
	nb_space = (fmt.min_width > len) ? fmt.min_width - len +
		(!i && !fmt.precision && fmt.point) : 0;
	sub_print_int(i, fmt, nb_space, nb_zero);
	return (len + nb_space - (!i && !fmt.precision && fmt.point));
}
