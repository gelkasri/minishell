/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:13:20 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/03 21:12:12 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_out_fd(char *cmd, int index)
{
	int		output_to_redir;

	if (index == 0 || cmd[index] == '<')
		return (0);
	output_to_redir = index - 1;
	if (ft_isdigit(cmd[output_to_redir]))
	{
		if (output_to_redir == 0 || ft_isspace(cmd[output_to_redir - 1]))
			return (1);
	}
	return (0);
}

static int	get_second_cursor(char *cmd, int i)
{
	while (cmd[i] == '<' || cmd[i] == '>')
		i++;
	while (ft_isspace(cmd[i]))
		i++;
	while (cmd[i] && !ft_isspace(cmd[i]))
		i++;
	return (i);
}

char	*remove_param(char *cmd, int i)
{
	char	*final;
	int		old_len;
	int		new_len;
	int		cursors[2];

	if (!cmd)
		return (NULL);
	old_len = ft_strlen(cmd);
	cursors[0] = has_out_fd(cmd, i) ? i - 1 : i;
	cursors[1] = get_second_cursor(cmd, i);
	new_len = old_len - (cursors[1] - cursors[0]);
	final = ft_memalloc(new_len + 1);
	ft_strncpy(final, cmd, cursors[0]);
	ft_strcpy(final + ft_strlen(final), cmd + cursors[1]);
	free(cmd);
	return (final);
}
