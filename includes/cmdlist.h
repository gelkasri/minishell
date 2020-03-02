/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:01:42 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 18:04:31 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CMDLIST_H
# define _CMDLIST_H

typedef struct		s_fdlist
{
	int				fd;
	struct s_fdlist	*next;
}					t_fdlist;

typedef struct		s_cmdlist
{
	void				*command;
	t_fdlist			*fd_in;
	t_fdlist			*fd_out;
	t_fdlist			*fd_out_err;
	struct s_cmdlist	*next;
}					t_cmdlist;

void		list_add_back(void **alst, void *new);

t_cmdlist	*cmdlist_new(void *command);
void		cmdlist_clear(t_cmdlist **lst, void (*del)(void *));
void		cmdlist_print(t_cmdlist *lst);

t_fdlist	*fdlist_new(int fd);
void		fdlist_clear(t_fdlist **lst);
void		fdlist_print(t_fdlist *lst);

#endif
