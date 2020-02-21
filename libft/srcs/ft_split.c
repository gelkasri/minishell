/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:43:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/10 10:38:13 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_next_sep(const char *str, char c, int start)
{
	if (start >= (int)ft_strlen(str))
		return (-1);
	while (str[start])
	{
		if (str[start] == c)
			return (start);
		start++;
	}
	return (ft_strlen(str));
}

static int	ft_nb_words(const char *str, char c)
{
	int res;
	int i;

	i = 0;
	res = 0;
	if (!str || !str[i])
		return (res);
	if (str[i] != c)
		res++;
	while (str[++i])
		if (str[i] != c && str[i - 1] == c)
			res++;
	return (res);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		sp;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	if (!s || !(res = malloc((ft_nb_words(s, c) + 1) * sizeof(char *))))
		return (NULL);
	sp = ft_next_sep(s, c, i);
	while (sp >= 0)
	{
		if ((sp - i) && !(res[count] =
				(char *)ft_memalloc((sp - i + 1) * sizeof(char))))
			return (0);
		j = 0;
		while (i < sp)
			res[count][j++] = s[i++];
		i++;
		sp = ft_next_sep(s, c, i);
		count = (j) ? count + 1 : count;
	}
	res[count] = NULL;
	return (res);
}
