/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 22:19:45 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/08 15:48:08 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "../../../includes/libft.h"

typedef int			(*t_ptr_fct)();

typedef struct		s_fct
{
	char			car;
	int				(*f)();
}					t_fct;

typedef struct		s_fmt
{
	char			conv;
	int				min_width;
	int				precision;
	char			zero;
	char			minus;
	char			point;
	char			plus;
	char			space;
	char			hash;
	unsigned int	len;
	char			hh;
	char			h;
	char			l;
	char			ll;
}					t_fmt;

int					ft_printf(const char *str, ...);

t_fct				*get_fct_list(void);
t_ptr_fct			get_fct(char c, t_fct *tab);

int					print_hexa_uc(va_list *ap, t_fmt fmt);
int					print_hexa_lc(va_list *ap, t_fmt fmt);
int					print_perc(va_list *ap, t_fmt fmt);
int					print_adr(va_list *ap, t_fmt fmt);
int					print_char(va_list *ap, t_fmt fmt);
int					print_str(va_list *ap, t_fmt fmt);
int					print_int(va_list *ap, t_fmt fmt);
int					print_long(va_list *ap, t_fmt fmt);
int					print_longlong(va_list *ap, t_fmt fmt);
int					print_uint(va_list *ap, t_fmt fmt);
int					print_ulong(va_list *ap, t_fmt fmt);
int					print_ulonglong(va_list *ap, t_fmt fmt);
int					print_hexa_uc_long(va_list *ap, t_fmt fmt);
int					print_hexa_lc_long(va_list *ap, t_fmt fmt);
int					print_hexa_uc_longlong(va_list *ap, t_fmt fmt);
int					print_hexa_lc_longlong(va_list *ap, t_fmt fmt);

int					ft_intlen(long long i);
int					ft_uintlen(unsigned long long i);
void				flags_cut(char *str);
t_fmt				fmt_parser(const char *str, va_list *ap);

#endif
