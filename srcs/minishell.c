/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:26:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/24 16:08:58 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static int	main_loop(char **line, t_list **env_list, int fd)
{
	int		i;
	char	*res;
	char	*trim;

	while (1)
	{
		*line = NULL;
		if (!fd)
			display_prompt(env_list);
		i = get_next_line(fd, line);
		if (i <= 0)
			break ;
		trim = ft_strtrim(*line, " ");
		i = exec_line(trim, env_list);
		res = ft_itoa(i);
		set_env_var("?", res, env_list);
		free(trim);
		free(*line);
		free(res);
	}
	return (0);
}

static int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (fd);
}

int			main(int argc, char **argv, char **envp)
{
	char	**line;
	t_list	**env_list;
	int		fd;

	if (argc > 1)
	{
		fd = open_file(argv[1]);
		if (fd < 0)
			return (127);
	}
	else
		fd = 0;
	if (!(env_list = init_env_list(envp)))
		return (MALLOC_ERROR);
	set_env_var("?", "0", env_list);
	if (!(line = ft_memalloc(sizeof(char *))))
		return (MALLOC_ERROR);
	if (!fd)
		ft_printf("%sBienvenue dans Minishell%s\n\n", GREEN, WHITE);
	main_loop(line, env_list, fd);
	if (*line)
		free(*line);
	free(line);
	return (0);
}
