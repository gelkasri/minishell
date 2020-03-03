/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:32:55 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/03 12:53:21 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Manage arrow keys and HOME/END keys
**
** Return values:
**   1 if buffer was updated (UP_KEY or DOWN_KEY)
**   0 if cursor moved (RIGHT_KEY or LEFT_KEY or HOME_KEY or END_KEY)
*/

static int	arrow_key_press(char c, t_editor *editor)
{
	editor->pos = get_cur_pos();
	if (c == UP_KEY)
		put_next_histo_in_buf(editor);
	else if (c == DOWN_KEY)
		put_prev_histo_in_buf(editor);
	else if (c == RIGHT_KEY)
		set_cur_pos(editor->pos.x + 1, editor->pos.y, editor);
	else if (c == LEFT_KEY)
		set_cur_pos(editor->pos.x - 1, editor->pos.y, editor);
	else if (c == HOME_KEY)
		set_cur_pos(editor->init_pos.x, editor->pos.y, editor);
	else if (c == END_KEY)
		set_cur_pos(editor->init_pos.x + ft_strlen(editor->buf),
					editor->pos.y, editor);
	if (c == UP_KEY || c == DOWN_KEY)
		return (1);
	return (0);
}

/*
** Move cursor to next or previous word
**   dir: direction of move:
**     1  if right move
**     -1 if left move
**
** A word contains only alphanumeric characters, no symbols or spaces
*/

static void	move_word(int dir, t_editor *editor)
{
	int len;
	int index;

	len = ft_strlen(editor->buf);
	index = get_cur_pos().x - editor->init_pos.x;
	while (index < len + 1 && index >= 0 && !ft_isalnum(editor->buf[index]))
		index += dir;
	while (index < len + 1 && index >= 0 && ft_isalnum(editor->buf[index]))
		index += dir;
	set_cur_pos(editor->init_pos.x + index, editor->pos.y, editor);
}

/*
** Manage ctrl+arrow keys
** When pressing ctrl+arrow key, following sequence is sent :
**   <esc>[1;5<A|B|C|D>
*/

static int	ctrl_arrow_key_press(t_editor *editor)
{
	char	c;
	char	seq[3];
	int		i;

	i = 0;
	ft_bzero(seq, 3);
	while (i < 3 && read(STDIN_FILENO, &seq[i], 1) >= 0)
	{
		if (seq[i] == 0 || seq[i] == ESC_KEY)
		{
			seq[i] = 0;
			break ;
		}
		i++;
	}
	if (seq[0] != ';' || seq[1] != '5' || seq[2] == 0)
		return (0);
	c = seq[2];
	editor->pos = get_cur_pos();
	if (c == RIGHT_KEY)
		move_word(1, editor);
	else if (c == LEFT_KEY)
		move_word(-1, editor);
	return (0);
}

/*
** Manage reading of escape sequences
**   Used when typing arrows keys (or home/end) with format "<esc>[A"
**                 or ctrl-arrow                with format "<esc>[1;5C"
**   see includes/keys.h for macro defined
**
** Return values:
**   1 if editor->buf has changed (UP_KEY of DOWM_KEY only)
**   0 else
*/

int			read_esc_seq(t_editor *editor)
{
	char	seq[2];
	int		i;

	i = 0;
	ft_bzero(seq, 2);
	while (i < 2 && read(STDIN_FILENO, &seq[i], 1) >= 0)
	{
		if (seq[i] == 0 || seq[i] == ESC_KEY)
			break ;
		i++;
	}
	if (seq[0] == '[')
	{
		if (seq[1] != '1')
			return (arrow_key_press(seq[1], editor));
		else
			return (ctrl_arrow_key_press(editor));
	}
	return (0);
}
