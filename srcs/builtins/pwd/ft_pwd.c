/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 11:28:58 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/22 14:56:37 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	ft_pwd(int ac, char **av, t_list **env_list)
{
	char	*cwd;

	(void)ac;
	(void)av;
	(void)env_list;
	if (!(cwd = getcwd(NULL, 0)))
	{
		ft_putstr_fd("pwd: cwd exceeds PATH_MAX\n", 2);
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}
