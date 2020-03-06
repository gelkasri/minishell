/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:29:39 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/06 12:58:50 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

char		*apply_changes(char *str, t_list **env_list)
{
	char	*buffer;
	char	*dup;
	int		test;

	test = str[(int)ft_strlen(str) - 1] == '~';
	if (!(dup = ft_strdup(str)))
		return (NULL);
	if (!(str = replace_tilde(dup, env_list)))
		return (NULL);
	if (test)
	{
		if (!(dup = ft_strjoin(str, "/")))
			return (free_return(str, NULL, NULL));
		free(str);
		str = dup;
	}
	if (!(buffer = apply_env_var(str, env_list)))
		return (free_return(str, NULL, NULL));
	return (free_return(str, NULL, buffer));
}

char		*get_full(char *str, t_list **env_list)
{
	char	*path;
	char	*curnt_wd;
	int		buf_len;
	char	*buffer;

	if (!(curnt_wd = get_env_var("PWD", env_list)))
		return (NULL);
	if (!str[0])
	{
		if (!(path = ft_strjoin(curnt_wd, "/")))
			return (free_return(curnt_wd, NULL, NULL));
		return (free_return(curnt_wd, NULL, path));
	}
	if (!(buffer = apply_changes(str, env_list)))
		return (free_return(curnt_wd, NULL, NULL));
	if (buffer[0] == '/')
		return ((free_return(curnt_wd, NULL, buffer)));
	buf_len = ft_strlen(buffer);
	path = ft_memalloc(buf_len + 2 + ft_strlen(curnt_wd));
	if (!path)
		return (free_return(curnt_wd, buffer, NULL));
	ft_strcpy(path, curnt_wd);
	ft_strcat(path, "/");
	ft_strcat(path, buffer);
	return (free_return(curnt_wd, buffer, path));
}

char		*get_path_and_name(char *buffer, char **req, t_list **env_list)
{
	int		i;
	char	*path;

	i = ft_strlen(buffer) - 1;
	while (i > 0 && !ft_isspace(buffer[i]))
		i--;
	if (!(path = get_full(buffer + i + (i ? 1 : 0), env_list)))
		return (NULL);
	i = ft_strlen(path) - 1;
	i = i < 0 ? 0 : i;
	while (i > 0 && path[i] != '/')
		i--;
	if (!(*req = ft_strdup(path + i + 1)))
		free_return(path, NULL, NULL);
	path[i] = '\0';
	return (path);
}

t_list		*read_dir(char *req, DIR *dir)
{
	struct dirent	*file;
	t_list			*final;
	t_list			*new;
	int				req_len;

	final = NULL;
	req_len = ft_strlen(req);
	while ((file = readdir(dir)) != NULL)
	{
		if ((int)ft_strlen(file->d_name) < req_len ||
		((file->d_name)[0] == '.' && req[0] != '.'))
			continue ;
		if (case_unsensitive_ncmp(file->d_name, req, req_len) == 0)
		{
			new = ft_lstnew(get_name(file));
			if (!new || !new->content)
			{
				ft_lstclear(&final, free);
				return (NULL);
			}
			ft_lstadd_back(&final, new);
		}
	}
	return (final);
}

t_list		*get_file_list(char *buffer, t_list **env_list)
{
	t_list	*list;
	DIR		*dir;
	char	*req;
	char	*path;

	path = get_path_and_name(buffer, &req, env_list);
	if (!path)
		return (NULL);
	dir = opendir(path);
	if (!path[0])
		dir = opendir("/");
	if (!dir)
		return (free_return(req, path, NULL));
	list = read_dir(req, dir);
	free(path);
	free(req);
	closedir(dir);
	return (list);
}
