/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:59:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/02 11:25:00 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Manage arrow keys.
**
** Return values:
**   1 if buffer was updated (UP_KEY or DOWN_KEY)
**   0 if cursor moved (RIGHT_KEY or LEFT_KEY)
*/

static int		arrow_key_press(char c, t_editor *editor)
{
	editor->pos = get_cur_pos();
	(void)editor;
	if (c == UP_KEY)
		put_next_histo_in_buf(editor);
	if (c == DOWN_KEY)
		put_prev_histo_in_buf(editor);
	if (c == RIGHT_KEY)
		set_cur_pos(editor->pos.x + 1, editor->pos.y, editor);
	if (c == LEFT_KEY)
		set_cur_pos(editor->pos.x - 1, editor->pos.y, editor);
	if (c == UP_KEY || c == DOWN_KEY)
		return (1);
	return (0);
}

/*
** Fonction that read keys pressed on keyboard
** \x1b = escape code for special presses (arrow keys)
** arrows keys are on 3 bytes : \x1b + '[' + 'A|B|C|D'
**
** Return values:
**   1 if editor->buf has changed
**   0 else
*/

static char		read_key(t_editor *editor)
{
	int		nread;
	char	c;
	char	seq[3];

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
		if (nread < 0)
			editor_error("read_key");
	if (nread == 0)
		return (0);
	if (c == '\x1b')
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return (0);
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return (0);
		if (seq[0] == '[')
			return (arrow_key_press(seq[1], editor));
		return (0);
	}
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
	t_list	*histo;

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
			if (ft_strlen(*line))
			{
				histo = ft_lstnew(ft_strdup(*line));
				ft_lstadd_front(editor->histo, histo);
				editor->histo_pos = NULL;
			}
			return (read_n);
		}
	}
}
