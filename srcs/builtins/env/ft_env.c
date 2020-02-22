/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:17:30 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/22 17:29:53 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_env(int ac, char **av, t_list **env_list)
{
	t_list		*env;
	char		**split;

	if (ac > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	env = *env_list;
	(void)av;
	while (env)
	{
		split = ft_split(env->content, '=');
		if (!split)
			return (1);
		if (split[1])
			ft_putendl(env->content);
		env = env->next;
	}
	return (0);
}
