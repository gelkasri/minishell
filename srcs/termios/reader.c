
#include "minishell.h"

/*
** Manage arrow keys.
**
** Return values:
**   1 if buffer was updated (UP_KEY or DOWN_KEY)
**   0 if cursor moved (RIGHT_KEY or LEFT_KEY)
*/

static int			arrow_key_press(char c, t_editor *editor)
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

/*
** Add a char in editor->buffer
**
** Return:
**  1 if a char has been added to buffer
**  0 else
*/

static int		add_to_editor_buffer(t_editor *editor, char c)
{
	char	*new_buffer;
	int		src_len;
	int		index;

	src_len = ft_strlen(editor->buf);
	new_buffer = ft_memalloc((src_len + 2) * sizeof(char));
	if (!new_buffer)
		return (0);
	index = editor->pos.x - editor->init_pos.x;
	ft_strncpy(new_buffer, editor->buf, index);
	new_buffer[index] = c;
	ft_strcat(new_buffer, editor->buf + index);
	free(editor->buf);
	editor->buf = new_buffer;
	return (1);
}

/*
** Delete a char in editor->buf
** The deleted char is the one present just before the cursor
**
** Return:
**  -1 if error
**  1 if a char has been deleted
**  0 else
*/

static int		delete_char_in_buffer(t_editor *editor)
{
	int		len;
	char	*new_buffer;
	int		index;

	len = ft_strlen(editor->buf);
	if (len == 0)
		return (0);
	if (!(new_buffer = ft_memalloc(len * sizeof(char))))
		return (-1);
	index = editor->pos.x - editor->init_pos.x;
	if (index <= 0)
		return (0);
	ft_strncpy(new_buffer, editor->buf, index - 1);
	ft_strcat(new_buffer, editor->buf + index);
	free(editor->buf);
	editor->buf = new_buffer;
	return (1);
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
	int		action_res;

	c = read_key(editor);
	editor->pos = get_cur_pos();
	old_cur_pos = get_cur_pos();
	action_res = 0;
	if (c == 0)
		return (0);
	if (c == ctrl_key('d'))
		return (-1);
	if (ft_strlen(editor->buf) == 0)
		editor->init_pos = get_cur_pos();
	if (ft_isprint(c))
		action_res = add_to_editor_buffer(editor, c);
	if (c == DEL_KEY)
		action_res = delete_char_in_buffer(editor);
	else if (c == ENTER_KEY)
	{
		ft_putendl("");
		return (1);
	}
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
