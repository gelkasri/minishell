/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:46:04 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 12:27:38 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		str_contains(const char *str, const char *lst)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (lst[j])
		{
			if (str[i] == lst[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
