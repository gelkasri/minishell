/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:34:46 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/12/09 21:00:56 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*get_flags(const char *str)
{
	int		i;
	char	*conv;

	conv = "cspdiuxX%nfge";
	i = 0;
	while (str[i] && ft_index(conv, str[i]) < 0)
		i++;
	if (!str[i])
		return (ft_strdup(""));
	return (ft_substr(str, 0, i + 1));
}

static int	get_precision(const char *str, t_fmt *fmt, int n, int i)
{
	char *res;

	fmt->precision = n;
	i--;
	while (i >= 0 && ft_isdigit(str[i]))
		i--;
	if (!(res = ft_substr(str, i + 1, ft_strlen(str))))
		return (-1);
	fmt->min_width = ft_atoi(res);
	free(res);
	return (1);
}

static int	get_width(const char *str, t_fmt *fmt)
{
	int		i;
	int		n;
	char	*res;
	int		j;

	j = ft_strlen(str) - 2;
	while (j >= 0 && ft_isalpha(str[j]))
		j--;
	i = j;
	while (i >= 0 && ft_isdigit(str[i]))
		i--;
	res = ft_substr(str, i + 1, j + 1);
	n = ft_atoi(res);
	free(res);
	if (ft_index((char *)str, '.') >= 0)
	{
		if ((get_precision(str, fmt, n, i)) < 0)
			return (-1);
	}
	else
	{
		fmt->min_width = n;
		fmt->precision = 0;
	}
	return (j);
}

static void	set_wildcard_width(char *flags, va_list *ap, t_fmt *res)
{
	int i;

	i = 0;
	while (flags[i])
		if (flags[i++] == '*')
		{
			if (ft_index(flags, '.') > i - 1 || ft_index(flags, '.') < 0)
				res->min_width = va_arg(*ap, int);
			else
				res->precision = va_arg(*ap, int);
		}
}

t_fmt		fmt_parser(const char *str, va_list *ap)
{
	t_fmt	res;
	char	*flags;
	int		j;

	flags = get_flags(str);
	res.len = ft_strlen(flags);
	res.conv = flags[res.len - 1];
	res.hh = (!(!ft_strstr(flags, "hh")));
	res.ll = (!(!ft_strstr(flags, "ll")));
	res.h = (!(!ft_strstr(flags, "h")));
	res.l = (!(!ft_strstr(flags, "l")));
	j = get_width(flags, &res);
	set_wildcard_width(flags, ap, &res);
	res.hash = (ft_index(flags, '#') >= 0);
	res.plus = (ft_index(flags, '+') >= 0);
	res.space = (ft_index(flags, ' ') >= 0 && !(ft_index(flags, '+') >= 0));
	res.minus = (ft_index(flags, '-') >= 0);
	res.point = (ft_index(flags, '.') >= 0);
	flags_cut(flags);
	res.zero = ((!res.point || res.conv == 's') && ft_index(flags, '0') >= 0
				&& !(ft_index(flags, '-') >= 0));
	free(flags);
	return (res);
}
