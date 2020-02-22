/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:26:16 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/24 18:16:57 by mle-moni         ###   ########.fr       */
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
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef int		(*t_fct_ptr)(int, char **, t_list **);

void			display_prompt(t_list **env_list);

char			**parse_line(char *line);
char			**parse_command(char *cmd);

int				exec_line(char *line, t_list **env_list);

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

int				ft_cd(int ac, char **av, t_list **env_list);
int				ft_echo(int ac, char **av, t_list **env_list);
int				ft_pwd(int ac, char **av, t_list **env_list);
int				ft_exit(int ac, char **av, t_list **env_list);
int				ft_export(int ac, char **av, t_list **env_list);
int				ft_env(int ac, char **av, t_list **env_list);

#endif
