/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 22:18:51 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/02 12:56:27 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			ft_printf(const char *str, ...)
{
	va_list		ap;
	t_fct		*fct_tab;
	t_fmt		fmt;
	int			n;

	if (!(fct_tab = get_fct_list()))
		return (-1);
	n = 0;
	va_start(ap, str);
	while (*str)
		if (*str == '%')
		{
			str++;
			fmt = fmt_parser(str, &ap);
			str += fmt.len;
			n += get_fct(fmt.conv, fct_tab)(&ap, fmt);
		}
		else
		{
			ft_putchar(*(str++));
			n++;
		}
	va_end(ap);
	free(fct_tab);
	return (n);
}
