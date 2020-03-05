/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:56:18 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/03 14:12:46 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			add_line_in_histo(char *line, t_editor *editor)
{
	t_list	*histo;

	if (ft_strlen(line))
	{
		histo = ft_lstnew(ft_strdup(line));
		ft_lstadd_front(editor->histo, histo);
		editor->histo_pos = NULL;
	}
}

/*
** Get next older line in cmds historic
** and put it in editor->buf
**
** Returns: new buf
*/

char			*put_next_histo_in_buf(t_editor *editor)
{
	char	*res;

	res = NULL;
	if (*(editor->histo) == NULL)
		return (NULL);
	if (editor->histo_pos == NULL && *(editor->histo))
	{
		editor->histo_pos = *(editor->histo);
		res = (char *)((*(editor->histo))->content);
		free(editor->buf_save);
		editor->buf_save = ft_strdup(editor->buf);
	}
	else if (editor->histo_pos->next)
	{
		editor->histo_pos = editor->histo_pos->next;
		res = (char *)(editor->histo_pos->content);
	}
	if (res)
	{
		free(editor->buf);
		editor->buf = ft_strdup(res);
	}
	return (res);
}

static void		replace_editor_buf(char *res, t_editor *editor)
{
	if (res)
	{
		free(editor->buf);
		editor->buf = ft_strdup(res);
	}
}

/*
** Get next recent line in cmds historic
** and put it in editor->buf
**
** iter is a t_list item that scans the history until it finds
**  the current position in the history
**
** Returns: new buf
*/

char			*put_prev_histo_in_buf(t_editor *editor)
{
	char	*res;
	t_list	*iter;

	res = NULL;
	iter = *(editor->histo);
	if (!*(editor->histo) || !editor->histo_pos)
		return (NULL);
	if (iter == editor->histo_pos)
	{
		editor->histo_pos = NULL;
		res = editor->buf_save;
	}
	while (iter->next && !res)
	{
		if (iter->next == editor->histo_pos)
		{
			editor->histo_pos = iter;
			res = (char *)(iter->content);
		}
		iter = iter->next;
	}
	replace_editor_buf(res, editor);
	return (res);
}
