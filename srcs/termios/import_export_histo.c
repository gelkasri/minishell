/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_export_histo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:17:59 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/05 16:04:02 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

char	*get_histo_file_path(t_list **env_list)
{
	char	*file_path;
	char	*home;

	home = get_env_var("HOME", env_list);
	if (!home)
		return (NULL);
	file_path = ft_memalloc(sizeof(char) *
							(ft_strlen(home) + ft_strlen(HISTO_FILE) + 2));
	if (!file_path)
		return (NULL);
	ft_strcpy(file_path, home);
	ft_strcat(file_path, "/");
	ft_strcat(file_path, HISTO_FILE);
	free(home);
	return (file_path);
}

void	export_histo(t_editor *editor, t_list **env_list)
{
	int		fd;
	char	*file_path;
	t_list	*histo;

	histo = *(editor->histo);
	file_path = get_histo_file_path(env_list);
	if (!file_path)
		return ;
	fd = open(file_path, O_WRONLY | O_TRUNC | O_CREAT, 0755);
	while (histo)
	{
		ft_putendl_fd((char *)histo->content, fd);
		histo = histo->next;
	}
	close(fd);
	free(file_path);
}

void	import_histo(t_editor *editor, t_list **env_list)
{
	int		fd;
	char	*file_path;
	char	*line;
	t_list	*new;

	file_path = get_histo_file_path(env_list);
	if (!file_path)
		return ;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return ;
	while (get_next_line(fd, &line))
	{
		new = ft_lstnew(line);
		ft_lstadd_back(editor->histo, new);
	}
	close(fd);
	free(line);
	free(file_path);
}
