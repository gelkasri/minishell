/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:46:04 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/04 17:21:52 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	*end_parser(t_cmdlist *cmdlist)
{
	cmdlist_clear(&cmdlist, free);
	return (NULL);
}

int			str_contains(const char *str, const char *lst)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (lst[j])
		{
			if (str[i] == lst[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int			get_path_len(char **str_ptr)
{
	int		i;
	char	*str;

	str = *str_ptr;
	i = 0;
	if (ft_isspace(str[i]))
	{
		*str_ptr += 1;
		return (get_path_len(str_ptr));
	}
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

void		set_which_fd(char *cmd, int index, int *which_fd)
{
	int		output_to_redir;

	if (cmd[index] == '<')
	{
		*which_fd = 0;
		return ;
	}
	*which_fd = 1;
	if (index == 0)
		return ;
	output_to_redir = index - 1;
	if (ft_isdigit(cmd[output_to_redir]))
	{
		if (output_to_redir == 0 || ft_isspace(cmd[output_to_redir - 1]))
		{
			if (cmd[output_to_redir] == '1' || cmd[output_to_redir] == '2')
			{
				*which_fd = cmd[output_to_redir] - '0';
				return ;
			}
			ft_putstr_fd("minishell: you can only redirect stdin and stdout\n",
			2);
			*which_fd = -21;
		}
	}
}
