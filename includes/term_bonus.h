/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:57:51 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/03 12:50:40 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TERM_BONUS_H
# define _TERM_BONUS_H

# include <termios.h>
# include <curses.h>
# include <term.h>
# include "keys.h"

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_editor
{
	char				*term_type;
	t_coord				pos;
	t_coord				init_pos;
	char				*buf;
	struct termios		orig_termios;
	t_list				**histo;
	t_list				*histo_pos;
	char				*buf_save;
}						t_editor;

/*
** term.c
*/

void					disable_raw_mode(void);
void					enable_raw_mode(void);
void					editor_error(const char *str);
t_editor				init_editor(t_list **env_list);

/*
** termios_reader.c
*/

int						termios_read_line(char **line, t_editor *editor);

/*
** add_delete_in_buffer.c
*/

int						add_to_editor_buffer(t_editor *editor, char c);
int						delete_char_in_buffer(t_editor *editor);

/*
** cursor.c
*/

t_coord					get_cur_pos(void);
void					set_cur_pos(int x, int y, t_editor *editor);

/*
** term_utils.c
*/

int						ctrl_key(char c);

/*
** histo.c
*/

void					add_line_in_histo(char *line, t_editor *editor);
char					*put_next_histo_in_buf(t_editor *editor);
char					*put_prev_histo_in_buf(t_editor *editor);

/*
** arrow_keys_action.c
*/

int						read_esc_seq(t_editor *editor);

#endif
