/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:26:16 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/06 13:37:44 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

# define RED		"\033[1;31m"
# define WHITE		"\033[0;m"
# define GREEN		"\033[1;32m"
# define BLUE		"\033[1;34m"
# define YELLOW		"\033[1;33m"

# define MALLOC_ERROR 2

# define DEBUG 0

# include "libft.h"
# include "term_bonus.h"
# include "cmdlist.h"
# include "completion.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

typedef int		(*t_fct_ptr)(int, char **, t_list **);

void			display_prompt(t_list **env_list);

char			**parse_line(char *line);
char			**parse_command(char *cmd);
char			*trim_quotes(char *substr);
char			*ft_substr_trim(char *str, int start, int len);
int				nb_arg(char *line, char delim);

char			*apply_env_var(char *str, t_list **env_list);
char			*replace_tilde(char *str, t_list **env_list);
void			*free_return(void *ptr, void *ptr2, void *ret_val);

t_cmdlist		*cmdparser(char *line);
int				str_contains(const char *str, const char *lst);

int				exec_line(char *line, t_list **env_list);

/*
** signals.c
*/
void			sub_exec(char *cmd_path, char **argv, char **envp);
int				free_and_return(char ***ptr, int ret_val);
int				handle_cmd_error(int error_type, const char *cmd);
void			trim_path(t_cmdlist *commands);
int				get_last_fd(t_fdlist *list);

int				get_child_exit_status(int status);
void			reset_signals(void);
void			ignore_signals(void);
int				get_exit_status(t_list **env_list);
void			set_exit_status_var(int status, t_list **env_list);

t_list			**init_env_list(char **envp);
char			**get_env_array(t_list **env_list);
char			*get_env_var(const char *var, t_list **env_list);
void			set_env_var(const char *var, const char *value, t_list **env_l);

void			free_str_arr(char **to_free);
char			*ft_strjoin3(char const *s1, char const *s2, char const *s3);

int				exec_builtins(char **argv, t_list **env_list);

char			*check_path(char *path, char *cmd);
char			*find_path(char *cmd, t_list **env_list);

/*
** Builtins
*/

int				export_no_param(t_list **env_list);
char			**split_in_2(char *str, char sep);

int				ft_cd(int ac, char **av, t_list **env_list);
int				ft_echo(int ac, char **av, t_list **env_list);
int				ft_pwd(int ac, char **av, t_list **env_list);
int				ft_exit(int ac, char **av, t_list **env_list);
int				ft_export(int ac, char **av, t_list **env_list);
int				ft_env(int ac, char **av, t_list **env_list);
int				ft_unset(int ac, char **av, t_list **env_list);
int				ft_history(int ac, char **av, t_list **env_list);

typedef struct	s_history
{
	char		*file_path;
	int			fd;
	int			ln_no;
	char		*line;
	t_list		*list;
	t_list		*new;
}				t_history;

/*
** Bonus
*/

int				get_pos(int *y, int *x);

#endif
