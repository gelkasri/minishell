/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:01:42 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 11:09:50 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CMDLIST_H
# define _CMDLIST_H

enum e_cmdtype {
	LAST,
	PIPE,
	TO_FILE,
	TO_FILE_APPEND,
	FROM_FILE
};

typedef struct		s_cmdlist
{
	void				*command;
	int					type;
	int					fd;
	struct s_cmdlist	*next;
}					t_cmdlist;

t_cmdlist	*cmdlist_new(void *command, int type, int fd);
void		cmdlist_add_front(t_cmdlist **alst, t_cmdlist *new);
int			cmdlist_size(t_cmdlist *lst);
void		cmdlist_clear(t_cmdlist **lst, void (*del)(void *));
void		cmdlist_print(t_cmdlist *lst);
void		cmdlist_add_back(t_cmdlist **alst, t_cmdlist *new);
t_cmdlist	*cmdlist_last(t_cmdlist *lst);
void		cmdlist_set(t_cmdlist *item, char *cmd, int type, int fd);

#endif