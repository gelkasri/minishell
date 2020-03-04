/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delete_in_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:24:03 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/04 16:16:51 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add a char in editor->buffer
**
** Return:
**  1 if a char has been added to buffer
**  0 else
*/

int		add_to_editor_buffer(t_editor *editor, char c)
{
	char	*new_buffer;
	int		src_len;
	int		index;

	if ((int)ft_strlen(editor->buf) + editor->init_pos.x > editor->win_size.x)
		return (0);
	src_len = ft_strlen(editor->buf);
	new_buffer = ft_memalloc((src_len + 2) * sizeof(char));
	if (!new_buffer)
		return (0);
	index = editor->pos.x - editor->init_pos.x;
	if (index < 0)
		return (0);
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

int		delete_char_in_buffer(t_editor *editor)
{
	int		len;
	char	*new_buffer;
	int		index;

	len = ft_strlen(editor->buf);
	if (len == 0)
		return (0);
	index = editor->pos.x - editor->init_pos.x;
	if (index <= 0)
		return (0);
	if (!(new_buffer = ft_memalloc(len * sizeof(char))))
		return (-1);
	ft_strncpy(new_buffer, editor->buf, index - 1);
	ft_strcat(new_buffer, editor->buf + index);
	free(editor->buf);
	editor->buf = new_buffer;
	return (1);
}
