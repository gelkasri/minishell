/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:32 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/05 19:33:13 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_file_list(char *buffer, t_list **env_list)
{
	t_list *res;

	(void)buffer;
	(void)env_list;
	if (buffer[0] != 'F')
		return (NULL);
	res = ft_lstnew(ft_strdup("Fichier_1"));
	if (ft_strncmp(buffer, "Fic", 3))
		ft_lstadd_front(&res, ft_lstnew(ft_strdup("File_2")));
	return (res);
}

void	replace_path_in_buf(char *file_name, t_editor *editor)
{
	int		i;
	char	*new_buf;

	if (!file_name)
		return ;
	i = ft_strlen(editor->buf) - 1;
	while (i >= 0 && editor->buf[i] != ' ' && editor->buf[i] != '/')
		i--;
	new_buf = ft_memalloc(sizeof(char) + i + ft_strlen(file_name) + 1);
	if (!new_buf)
		return ;
	ft_strncpy(new_buf, editor->buf, i + 1);
	ft_strcat(new_buf, file_name);
	free(editor->buf);
	editor->buf = new_buf;
}

void	print_comp_res(t_list *comp_list)
{
	while (comp_list)
	{
		ft_putstr((char *)comp_list->content);
		ft_putchar('\t');
		comp_list = comp_list->next;
	}
	ft_putendl("");
}

void	apply_completion(t_editor *editor, t_list **env_list)
{
	t_list	*comp_list;
	int		len;

	(void)editor;
	comp_list = get_file_list(editor->buf, env_list);
	if (!comp_list)
		return ;
	len = ft_lstsize(comp_list);
	if (len == 1)
		replace_path_in_buf((char *)comp_list->content, editor);
	else
	{
		ft_putendl("");
		print_comp_res(comp_list);
		display_prompt(env_list);
	}
	ft_lstclear(&comp_list, free);
}
