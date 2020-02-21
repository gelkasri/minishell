/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:19:56 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 19:08:50 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TEMP FCT - For tests
*/

int			ft_env(int argc, char **argv, char **envp)
{
	int i;

	(void)argc;
	(void)argv;
	i = 0;
	while (envp[i])
		ft_putendl(envp[i++]);
	return (0);
}

t_fct_ptr	get_fct_builtins(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (NULL);
	return (NULL);
}

int			exec_builtins(char **argv, char **envp)
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
	ret = fct(argc, argv, envp);
	return (ret);
}
