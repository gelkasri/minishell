/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:59:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/05 19:33:36 by gel-kasr         ###   ########.fr       */
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
	get_window_size(editor);
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
	editor->pos.y = get_cur_pos().y;
	editor->init_pos.y = get_cur_pos().y;
	old_cur_pos.y = get_cur_pos().y;
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
	if (c == ctrl_key('y'))
		set_cur_pos(old_cur_pos.x + ft_strlen(editor->copy_buf),
					old_cur_pos.y, editor);
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

static int		process_key_press(t_editor *editor, t_list **env_list)
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
	else if (c == ctrl_key('k'))
		cut_copy_after_cursor(1, editor);
	else if (c == ctrl_key('j'))
		cut_copy_after_cursor(0, editor);
	else if (c == ctrl_key('y'))
		paste_after_cursor(editor);
	else if (c == ENTER_KEY)
	{
		ft_putendl("");
		return (1);
	}
	else if (c == TAB_KEY)
		apply_completion(editor, env_list);
	key_action(c, old_cur_pos, editor);
	return (0);
}

int				termios_read_line(char **line, t_editor *editor,
									t_list **env_list)
{
	int		read_n;

	enable_raw_mode();
	*line = NULL;
	editor->init_pos = get_cur_pos();
	while (1)
	{
		if ((read_n = process_key_press(editor, env_list)) < 0)
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
