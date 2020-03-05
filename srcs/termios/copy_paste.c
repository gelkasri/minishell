/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:17:29 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/03 16:21:02 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Copy or cut all chars after the cursor into the editor->copy_buf
**
** if cut = 0: juste copy the line (ctrl+j)
** else :      cut the line        (ctrl+k)
*/

void	cut_copy_after_cursor(int cut, t_editor *editor)
{
	int index;

	index = editor->pos.x - editor->init_pos.x;
	if (index == (int)ft_strlen(editor->buf))
		return ;
	free(editor->copy_buf);
	editor->copy_buf = ft_strdup(editor->buf + index);
	if (cut)
		editor->buf[index] = 0;
}

/*
** Paste line after cursor, with ctrl+y key
*/

void	paste_after_cursor(t_editor *editor)
{
	int			i;
	t_coord		old_cur_pos;

	old_cur_pos = get_cur_pos();
	i = ft_strlen(editor->copy_buf) - 1;
	while (i >= 0)
	{
		add_to_editor_buffer(editor, editor->copy_buf[i]);
		i--;
	}
}
