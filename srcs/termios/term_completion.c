/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:32 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/06 13:36:33 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		dir;
	int		max_len;

	max_len = get_max_name_len(comp_list);
	while (comp_list)
	{
		dir = ((char *)comp_list->content)
			[ft_strlen(comp_list->content) - 1] == '/';
		ft_printf("%s%-*s%s\t", (dir) ? RED : WHITE,
					max_len, (char *)comp_list->content, WHITE);
		comp_list = comp_list->next;
	}
	ft_putendl("");
}

char	*find_common_path(t_list *comp_list)
{
	int		end;
	t_list	*lst_ptr;
	char	c;
	int		i;
	char	*res;

	if (!comp_list || !comp_list->next)
		return (NULL);
	end = 0;
	i = -1;
	while (!end)
	{
		lst_ptr = comp_list;
		c = ((char *)lst_ptr->content)[++i];
		while (lst_ptr && !end)
		{
			if (((char *)lst_ptr->content)[i] == 0 ||
				c != ((char *)lst_ptr->content)[i])
				end = 1;
			lst_ptr = lst_ptr->next;
		}
	}
	res = ft_strdup((char *)comp_list->content);
	res[i] = 0;
	return (res);
}

void	apply_completion(t_editor *editor, t_list **env_list)
{
	t_list	*comp_list;
	int		len;
	char	*common;

	(void)editor;
	comp_list = get_file_list(editor->buf, env_list);
	if (!comp_list)
		return ;
	len = ft_lstsize(comp_list);
	if (len == 1)
		replace_path_in_buf((char *)comp_list->content, editor);
	else
	{
		common = find_common_path(comp_list);
		replace_path_in_buf(common, editor);
		ft_putendl("");
		print_comp_res(comp_list);
		display_prompt(env_list);
		free(common);
	}
	ft_lstclear(&comp_list, free);
}
