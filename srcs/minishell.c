/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:26:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/04 16:05:01 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <curses.h>
#include <term.h>

t_list		***g_env_list;

void		handle_sigint(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	set_env_var("?", "1", *g_env_list);
	ft_putstr("\n");
	display_prompt(*g_env_list);
}

/*
** Main loop that read cmds and execute, until read_line fct == 0
**   (ctrl+d or EOF)
**
** isatty(STDIN_FILENO) check if stdin is an interactive terminal or not
*/

static int	main_loop(char **line, t_list **env_list, int fd, t_editor *editor)
{
	int		i;
	char	*trim;

	while (1)
	{
		*line = NULL;
		if (!fd && isatty(STDIN_FILENO))
			display_prompt(env_list);
		signal(SIGINT, handle_sigint);
		if (fd == 0 && isatty(STDIN_FILENO))
			i = termios_read_line(line, editor);
		else
			i = get_next_line(fd, line);
		if (i <= 0)
			ft_exit(1, NULL, env_list);
		trim = ft_strtrim(*line, " ");
		i = exec_line(trim, env_list);
		free(trim);
		free(*line);
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

static int	main_init(char ***line, t_editor *editor, char **envp, int fd)
{
	if (!(*line = ft_memalloc(sizeof(char *))))
		return (MALLOC_ERROR);
	g_env_list = ft_memalloc(sizeof(t_list **));
	if (!g_env_list || !(*g_env_list = init_env_list(envp)))
		return (MALLOC_ERROR);
	set_env_var("?", "0", *g_env_list);
	if (!fd && isatty(STDIN_FILENO))
	{
		*editor = init_editor(*g_env_list);
		ft_printf("%sBienvenue dans Minishell%s\n\n", GREEN, WHITE);
	}
	else
		set_env_var("INTERACTIVE", "NO", *g_env_list);
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	char		**line;
	t_list		**env_list;
	int			fd;
	t_editor	editor;

	if (argc > 1)
	{
		fd = open_file(argv[1]);
		if (fd < 0)
			return (127);
	}
	else
		fd = 0;
	main_init(&line, &editor, envp, fd);
	env_list = *g_env_list;
	main_loop(line, env_list, fd, &editor);
	if (*line)
		free(*line);
	free(line);
	return (0);
}
