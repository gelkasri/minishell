/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 04:51:54 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/09 21:02:01 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static t_fct	new_fct(char car, void (*f))
{
	t_fct res;

	res.car = car;
	res.f = f;
	return (res);
}

int				ft_void(void)
{
	return (0);
}

t_ptr_fct		get_fct(char c, t_fct *tab)
{
	int i;

	if (!tab || !c)
		return (NULL);
	i = -1;
	while (tab[++i].car)
		if (c == tab[i].car)
		{
			return (tab[i].f);
		}
	return (ft_void);
}

/*
** Create functions tab
** Last item is set to car = 0 and f = NULL
*/

t_fct			*get_fct_list(void)
{
	t_fct *tab;

	tab = (t_fct *)malloc(sizeof(*tab) * 12);
	if (!tab)
		return (NULL);
	tab[0] = new_fct('c', print_char);
	tab[1] = new_fct('s', print_str);
	tab[2] = new_fct('d', print_int);
	tab[3] = new_fct('i', print_int);
	tab[4] = new_fct('x', print_hexa_lc);
	tab[5] = new_fct('X', print_hexa_uc);
	tab[6] = new_fct('%', print_perc);
	tab[7] = new_fct('p', print_adr);
	tab[8] = new_fct('u', print_uint);
	tab[9] = new_fct(0, NULL);
	return (tab);
}
