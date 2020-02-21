/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:17:24 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/21 17:39:32 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_n_option(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp("-n", str) == 0)
		return (1);
	return (0);
}

/*
** Mime the behavior of echo
** ac = number of parameters
** av = array of parameters
*/

int			ft_echo(int ac, char **av, char **envp)
{
	int	n_option;
	int	i;

	(void)envp;
	n_option = 0;
	if (ac > 1)
		n_option = get_n_option(av[1]);
	i = 1;
	if (n_option)
		i = 2;
	while (i < ac)
	{
		ft_putstr_fd(av[i], 1);
		i++;
		if (i < ac)
			write(1, " ", 1);
	}
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
