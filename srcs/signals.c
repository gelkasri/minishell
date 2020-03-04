/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:36:36 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/04 17:05:20 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_child_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr("Quit: ");
			ft_putnbr(SIGQUIT);
		}
		ft_putendl("");
		return (128 + WTERMSIG(status));
	}
	return (0);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int		get_exit_status(t_list **env_list)
{
	char	*str;
	int		res;

	if ((str = get_env_var("?", env_list)))
		res = ft_atoi(str);
	else
		res = 0;
	free(str);
	return (res);
}

void	set_exit_status_var(int status, t_list **env_list)
{
	char	*ret_var;

	if (!(ret_var = ft_itoa(status)))
		return ;
	set_env_var("?", ret_var, env_list);
	free(ret_var);
}
