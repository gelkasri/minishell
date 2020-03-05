/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:57:51 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/05 17:44:11 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TERM_BONUS_H
# define _TERM_BONUS_H

# include <termios.h>
# include <curses.h>
# include <term.h>
# include "keys.h"

# define HISTO_FILE ".minishell_history"
# define HISTO_FILE_ERR "History file not available"

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_editor
{
	char				*term_type;
	t_coord				win_size;
	t_coord				pos;
	t_coord				init_pos;
	char				*buf;
	struct termios		orig_termios;
	t_list				**histo;
	t_list				*histo_pos;
	char				*buf_save;
	char				*copy_buf;
}						t_editor;

t_editor				**g_editor;

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
int						get_window_size(t_editor *editor);

/*
** histo.c
*/

void					add_line_in_histo(char *line, t_editor *editor);
char					*put_next_histo_in_buf(t_editor *editor);
char					*put_prev_histo_in_buf(t_editor *editor);

/*
** import_export_histo.c
*/

char					*get_histo_file_path(t_list **env_list);
void					export_histo(t_editor *editor, t_list **env_list);
void					import_histo(t_editor *editor, t_list **env_list);

/*
** arrow_keys_action.c
*/

int						read_esc_seq(t_editor *editor);

/*
** copy_paste.c
*/

void					cut_copy_after_cursor(int cut, t_editor *editor);
void					paste_after_cursor(t_editor *editor);
#endif
