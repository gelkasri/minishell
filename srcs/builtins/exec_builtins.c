/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:19:56 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 16:57:52 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fct_ptr	get_fct_builtins(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ft_echo);
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
