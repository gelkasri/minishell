/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:59:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/03 12:34:16 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction that read keys pressed on keyboard
** \x1b = escape code for special presses (arrow keys)
** arrows keys are on 3 bytes : ESC_KEY + '[' + 'A|B|C|D'
**
** Return values:
**   1 if editor->buf has changed
**   0 else
*/

static char		read_key(t_editor *editor)
{
	int		nread;
	char	c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
		if (nread < 0)
			editor_error("read_key");
	if (nread == 0)
		return (0);
	if (c == ESC_KEY)
		return (read_esc_seq(editor));
	else
		return (c);
}

static void		key_action(char c, t_coord old_cur_pos, t_editor *editor)
{
	int action_res;

	action_res = 0;
	if (ft_isprint(c))
		action_res = add_to_editor_buffer(editor, c);
	if (c == DEL_KEY)
		action_res = delete_char_in_buffer(editor);
	if (c)
	{
		set_cur_pos(editor->init_pos.x, editor->init_pos.y, editor);
		ft_putstr("\x1b[K");
		ft_putstr(editor->buf);
		if (action_res)
			set_cur_pos(old_cur_pos.x + 1, old_cur_pos.y, editor);
	}
	if (c == DEL_KEY)
		set_cur_pos(old_cur_pos.x - 1, old_cur_pos.y, editor);
}

/*
** Manage a single key press
** - read the pressed key
** - depending on its value, perform action
**
** Return values:
**   0 if empty key or printable key
**   1 if \n
**   -1 if eof (ctrl+d)
**
** ft_putstr("\x1b[K"): to erase current line after cursor
*/

static int		process_key_press(t_editor *editor)
{
	char	c;
	t_coord	old_cur_pos;

	c = read_key(editor);
	editor->pos = get_cur_pos();
	old_cur_pos = get_cur_pos();
	if (c == 0)
		return (0);
	else if (c == ctrl_key('d'))
		return (-1);
	else if (c == ENTER_KEY)
	{
		ft_putendl("");
		return (1);
	}
	key_action(c, old_cur_pos, editor);
	return (0);
}

int				termios_read_line(char **line, t_editor *editor)
{
	int		read_n;

	enable_raw_mode();
	*line = NULL;
	editor->init_pos = get_cur_pos();
	while (1)
	{
		if ((read_n = process_key_press(editor)) < 0)
			return (-1);
		if (read_n)
		{
			free(*line);
			*line = ft_strdup(editor->buf);
			free(editor->buf);
			editor->buf = ft_strdup("");
			add_line_in_histo(*line, editor);
			disable_raw_mode();
			return (read_n);
		}
	}
}
