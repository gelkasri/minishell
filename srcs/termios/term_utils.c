/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:58:38 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/04 16:19:31 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int		ctrl_key(char c)
{
	if (ft_tolower(c) >= 'a' && ft_tolower(c) <= 'z')
		return (ft_tolower(c) - 96);
	return (-1);
}

int		get_window_size(t_editor *editor)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (-1);
	else
	{
		editor->win_size.x = ws.ws_col;
		editor->win_size.y = ws.ws_row;
	}
	return (0);
}
