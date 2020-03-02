/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:46:16 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 11:09:58 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	*cmdlist_new(void *command, int type, int fd)
{
	t_cmdlist	*new;

	new = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	new->command = command;
	new->fd = fd;
	new->type = type;
	new->next = NULL;
	return (new);
}

void		cmdlist_add_front(t_cmdlist **alst, t_cmdlist *new)
{
	new->next = *alst;
	*alst = new;
}

int			cmdlist_size(t_cmdlist *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void		cmdlist_clear(t_cmdlist **lst, void (*del)(void *))
{
	t_cmdlist	*temp;
	t_cmdlist	*iter;

	if (!lst || !(*lst))
		return ;
	iter = *lst;
	while (iter)
	{
		temp = iter->next;
		del(iter->command);
		free(iter);
		iter = temp;
	}
	*lst = NULL;
	lst = NULL;
}
