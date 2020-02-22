/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:19:56 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/22 16:16:18 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TEMP FCT - For tests of env builtin
** TODO: To move
*/

t_fct_ptr	get_fct_builtins(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(str, "env") == 0)
		return (ft_env);
	if (ft_strcmp(str, "pwd") == 0)
		return (ft_pwd);
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit);
	if (ft_strcmp(str, "export") == 0)
		return (ft_export);
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
