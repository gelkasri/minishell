/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 11:28:58 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/22 11:38:55 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include <errno.h>
#define PATH_MAX 256

int	ft_pwd(int ac, char **av, t_list **env_list)
{
	char	cwd_buffer[PATH_MAX];

	if (ac > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	if (!getcwd(cwd_buffer, PATH_MAX))
	{
		ft_putstr_fd("pwd: cwd exceeds PATH_MAX\n", 2);
		return (1);
	}
	ft_putendl_fd(cwd_buffer, 1);
	return (0);
}
