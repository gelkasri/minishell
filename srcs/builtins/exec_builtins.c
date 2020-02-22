/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:19:56 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 23:18:30 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TEMP FCT - For tests of env builtin
** TODO: To move
*/

int			ft_env(int argc, char **argv, t_list **env_list)
{
	t_list *env;

	env = *env_list;
	(void)argc;
	(void)argv;
	while (env)
	{
		ft_putendl(env->content);
		env = env->next;
	}
	return (0);
}

t_fct_ptr	get_fct_builtins(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(str, "env") == 0)
		return (ft_env);
	return (NULL);
}

int			exec_builtins(char **argv, t_list **env_list)
{
	int			ret;
	t_fct_ptr	fct;
	int			argc;

	ret = -1;
	argc = 0;
	while (argv[argc])
		argc++;
	if (!(fct = get_fct_builtins(argv[0])))
		return (-1);
	ret = fct(argc, argv, env_list);
	return (ret);
}
