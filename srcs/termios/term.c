/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:51:24 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/02 11:07:01 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <curses.h>
#include <term.h>

struct termios	orig_termios;

void			editor_error(const char *str)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(str);
	exit(1);
}

static void		disable_raw_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		editor_error("disable_raw_mode");
}

/*
** Fonction that enable raw mode != canonical mode
** ECHO: disable printing on terminal
** ICANON: turn off canonical mode (read byte by bute)
** IXON - IEXTEN - ICRNL: disable ctrl-S ctrl-Q ctrl-V ctrl-O ctrl-M
** OPOST: disable output processing
** VMIN - VTIME: timeout for read
*/

static void		enable_raw_mode(struct termios orig)
{
	struct termios raw;

	raw = orig;
	orig_termios = orig;
	atexit(disable_raw_mode);
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		editor_error("enable_raw_mode");
}

t_editor		init_editor(t_list **env_list)
{
	t_editor	editor;

	editor.term_type = get_env_var("TERM", env_list);
	if (tcgetattr(STDIN_FILENO, &(editor.orig_termios)) == -1)
		editor_error("init_editor");
	editor.buf = ft_strdup("");
	editor.histo = ft_memalloc(sizeof(t_list *));
	editor.histo_pos = NULL;
	editor.buf_save = ft_strdup("");
	enable_raw_mode(editor.orig_termios);
	return (editor);
}
