/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:36 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/25 16:47:13 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**split_in_2(char *str, char sep)
{
	int		index;
	char	**res;

	index = ft_index(str, sep);
	if (!(res = ft_memalloc(3 * sizeof(char *))))
		return (NULL);
	if (index <= 0)
		res[0] = ft_strdup(str);
	else
	{
		res[0] = ft_substr(str, 0, index);
		res[1] = ft_substr(str, index + 1, ft_strlen(str) - index);
	}
	return (res);
}
