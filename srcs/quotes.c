/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:22:25 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/25 15:05:11 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static int	ft_index_2(char *str, char c, char c2)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c || str[i] == c2)
			return (i);
		i++;
	}
	return (-1);
}

/*
** we assume that quotes are always by group of 2
** (because the error would have been raised before this function)
*/

static char	*trim_this_part(int *i, char *str, char quote)
{
	char	*new;
	int		len_of_this_part;
	int		matching_quote_index;

	new = ft_memalloc(ft_strlen(str) - 1);
	if (!new)
	{
		free(str);
		return (NULL);
	}
	ft_strncpy(new, str, *i);
	matching_quote_index = ft_index(str + (*i) + 1, quote) + (*i) + 1;
	len_of_this_part = ft_index(str + (*i) + 1, quote);
	ft_strncpy(new + (*i), str + (*i) + 1, len_of_this_part);
	(*i) += len_of_this_part;
	ft_strcpy(new + (*i), str + matching_quote_index + 1);
	free(str);
	return (new);
}

char		*trim_quotes(char *str)
{
	char	*final;
	int		i;
	int		index;

	i = 0;
	if (ft_strlen(str) == 0)
		return (NULL);
	if (!(final = ft_strdup(str)))
		return (NULL);
	while (final[i])
	{
		if ((index = ft_index_2(final + i, '"', '\'')) == -1)
			return (final);
		i += index;
		final = trim_this_part(&i, final, final[i]);
		if (!final)
			return (NULL);
	}
	return (final);
}
