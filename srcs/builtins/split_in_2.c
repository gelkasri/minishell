/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:36 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/24 17:45:27 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_general_case(char *str, int index)
{
	char	**ret;
	char	*str2;

	str2 = str + index + 1;
	str[index] = '\0';
	ret = malloc(3 * sizeof(char*));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(str);
	ret[1] = ft_strdup(str2);
	str[index] = '=';
	if (!ret[0] || !ret[1])
	{
		free_str_arr(ret);
		free(ret);
		return (NULL);
	}
	ret[2] = NULL;
	return (ret);
}

static char	**dont_use_last_char(char *str)
{
	char	**ret;
	char	bckp;

	bckp = str[ft_strlen(str) - 1];
	str[ft_strlen(str) - 1] = '\0';
	ret = malloc(2 * sizeof(char*));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(str);
	str[ft_strlen(str)] = bckp;
	if (!ret[0])
	{
		free_str_arr(ret);
		free(ret);
		return (NULL);
	}
	ret[1] = NULL;
	return (ret);
}

static char	**continue_split(char *str, int index)
{
	if (index == (int)(ft_strlen(str) - 1))
		return (dont_use_last_char(str));
	return (split_general_case(str, index));
}

char		**split_in_2(char *str, char sep)
{
	char	**ret;
	int		index;

	if (!str)
		return (NULL);
	index = ft_index(str, sep);
	if (index <= 0)
	{
		ret = malloc(2 * sizeof(char*));
		if (!ret)
			return (NULL);
		ret[0] = ft_strdup(index == 0 ? str + 1 : str);
		if (!ret[0])
		{
			free_str_arr(ret);
			free(ret);
			return (NULL);
		}
		ret[1] = NULL;
		return (ret);
	}
	ret = continue_split(str, index);
	return (ret);
}
