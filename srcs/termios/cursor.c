/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:54:40 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/02 10:55:49 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Return current cursor position.
** Write position in a buffer, format <ESC>[10;15R
** where y = 10 and x = 15
*/

t_coord		get_cur_pos(void)
{
	char			buf[30];
	int				i;
	struct termios	term;
	struct termios	restore;
	t_coord			c;

	ft_bzero(buf, 30);
	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	write(0, "\033[6n", 4);
	i = 0;
	while (i == 0 || buf[i - 1] != 'R')
		read(0, &buf[i++], 1);
	i = ft_index(buf, '[') + 1;
	c.y = ft_atoi(buf + i);
	i = ft_index(buf, ';') + 1;
	c.x = ft_atoi(buf + i);
	tcsetattr(0, TCSANOW, &restore);
	return (c);
}

void		set_cur_pos(int x, int y, t_editor *editor)
{
	if (x > editor->init_pos.x + (int)ft_strlen(editor->buf))
		x = editor->init_pos.x + (int)ft_strlen(editor->buf);
	if (x < editor->init_pos.x)
		x = editor->init_pos.x;
	editor->pos.x = x;
	editor->pos.y = y;
	ft_putstr("\x1b[");
	ft_putnbr(y);
	ft_putstr(";");
	ft_putnbr(x);
	ft_putstr("H");
}
