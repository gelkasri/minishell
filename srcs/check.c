/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:36:06 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/06 16:00:26 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_fd_ret(int ret, t_list **env_list)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	set_env_var("?", "258", env_list);
	return (ret);
}

int			check_line(char *str, t_list **env_list)
{
	int		quotes[2];
	int		i;
	int		old_i;

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quotes[0] = (quotes[0] + 1) % 2;
		else if (str[i] == '"')
			quotes[1] = (quotes[1] + 1) % 2;
		else if (str[i] == '|' && !(quotes[0] || quotes[1]))
		{
			old_i = i++;
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|')
				return (print_fd_ret(1, env_list));
		}
		i++;
	}
	return (0);
}
