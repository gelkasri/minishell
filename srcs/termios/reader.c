
#include "minishell.h"

static char		read_key(void)
{
	int		nread;
	char	c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
		if (nread < 0)
			editor_error("read_key");
	if (nread == 0)
		return (0);
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

static int		process_key_press(t_editor *editor)
{
	char	c;

	c = read_key();
	if (c == 0)
		return (0);
	if (c == ctrl_key('d'))
		return (-1);
	if (ft_strlen(editor->buf) == 0)
	{
		editor->pos = get_cur_pos();
		editor->init_pos = editor->pos;
	}
	if (ft_isprint(c))
	{
		add_to_editor_buffer(editor, c);
		set_cur_pos(editor->init_pos.x, editor->init_pos.y);
		ft_putstr(editor->buf);
		return (0);
	}
	if (c == ENTER_KEY)
	{
		ft_putendl("");
		return (1);
	}
	return (0);
}

int				termios_read_line(char **line, t_editor *editor)
{
	int		read_n;

	*line = NULL;
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
			return (read_n);
		}
	}
}
