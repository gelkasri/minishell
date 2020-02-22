/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:39:53 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/22 16:46:18 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** parse_and_export takes a string formatted as follow:
** KEY[=VALUE]
** (=VALUE is facultative)
*/

int		parse_and_export(char *str, t_list **env_list)
{
	char	**split;

	split = ft_split(str, '=');
	if (!split)
		return (1);
	if (split[0] && split[1])
		set_env_var(split[0], split[1], env_list);
	else if (split[0])
		set_env_var(split[0], "", env_list);
	free_str_arr(split);
	free(split);
	return (0);
}

/*
** ft_export set the environment variables with all strings in char **av
** if ac=1, it displays the environment variables
*/

int		ft_export(int ac, char **av, t_list **env_list)
{
	int i;

	i = 1;
	if (ac == 1)
	{
		ft_env(ac, av, env_list);
		return (0);
	}
	while (ac > i)
	{
		parse_and_export(av[i], env_list);
		i++;
	}
	return (0);
}
