
#include "minishell.h"

static void		arrow_key_press(char c, t_editor *editor)
{
	editor->pos = get_cur_pos();
	(void)editor;
	if (c == UP_KEY)
		put_next_histo_in_buf(editor);
	if (c == DOWN_KEY)
		put_prev_histo_in_buf(editor);
	if (c == RIGHT_KEY &&
		editor->pos.x < editor->init_pos.x + (int)ft_strlen(editor->buf))
		editor->pos.x++;
	if (c == LEFT_KEY && editor->pos.x > editor->init_pos.x)
		editor->pos.x--;
	set_cur_pos(editor->pos.x, editor->pos.y);
}

/*
** Fonction that read keys pressed on keyboard
** \x1b = escape code for special presses (arrow keys)
** arrows keys are on 3 bytes : \x1b + '[' + 'A|B|C|D'
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
			return ('\x1b');
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return ('\x1b');
		if (seq[0] == '[')
			arrow_key_press(seq[1], editor);
		return ('\x1b');
	}
	else
		return (c);
}

static int		add_to_editor_buffer(t_editor *editor, char c)
{
	char	*tmp;
	int		src_len;

	src_len = ft_strlen(editor->buf);
	tmp = ft_memalloc((src_len + 2) * sizeof(char));
	if (!tmp)
		return (-1);
	ft_strcpy(tmp, editor->buf);
	tmp[src_len] = c;
	free(editor->buf);
	editor->buf = tmp;
	return (0);
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

	c = read_key(editor);
	if (c == 0)
		return (0);
	if (c == ctrl_key('d'))
		return (-1);
	if (ft_strlen(editor->buf) == 0)
		editor->init_pos = get_cur_pos();
	if (ft_isprint(c))
		add_to_editor_buffer(editor, c);
	else if (c == ENTER_KEY)
	{
		ft_putendl("");
		return (1);
	}
	set_cur_pos(editor->init_pos.x, editor->init_pos.y);
	ft_putstr("\x1b[K");
	ft_putstr(editor->buf);
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
