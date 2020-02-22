/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:44:41 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/22 17:03:41 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*check_path(char *path, char *cmd, struct stat *buf)
{
	char	*join;
	char	*res;

	res = NULL;
	if (!(join = ft_strjoin3(path, "/", cmd)))
		return (NULL);
	if (lstat(join, buf) == 0)
		res = ft_strdup(join);
	free(join);
	return (res);
}

/*
** Find the full path of an executable, using $PATH
** - cmd = executable to find
** - env_list = list of environement variables
**
** Return values :
** - full path if executable found
** - NULL if executable not found
*/

char			*find_path(char *cmd, t_list **env_list)
{
	char		**split;
	int			i;
	char		*tmp;
	char		*res;
	struct stat	*buf;

	tmp = get_env_var("PATH", env_list);
	if (!(buf = malloc(sizeof(*buf))))
		return (NULL);
	if (!(split = ft_split(tmp, ':')))
		return (NULL);
	free(tmp);
	i = -1;
	res = NULL;
	while (split[++i] && !res)
		res = check_path(split[i], cmd, buf);
	free_str_arr(split);
	free(split);
	free(buf);
	return (res);
}
