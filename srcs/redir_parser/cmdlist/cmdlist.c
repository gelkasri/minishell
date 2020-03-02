/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:46:16 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 18:23:54 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	*cmdlist_new(void *command)
{
	t_cmdlist	*new;

	new = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	new->command = command;
	new->fd_in = NULL;
	new->fd_out = NULL;
	new->next = NULL;
	return (new);
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
		fdlist_clear(&(iter->fd_in));
		fdlist_clear(&(iter->fd_out));
		fdlist_clear(&(iter->fd_out_err));
		free(iter);
		iter = temp;
	}
	*lst = NULL;
	lst = NULL;
}

void		cmdlist_print(t_cmdlist *lst)
{
	ft_putstr("displaying cmdlist:\n");
	while (lst)
	{
		ft_putstr("cmd = ");
		ft_putstr(lst->command);
		ft_putstr("\nfd_in = : ");
		fdlist_print(lst->fd_in);
		ft_putstr("\nfd_out = : ");
		fdlist_print(lst->fd_out);
		ft_putstr("\nfd_out_err = : ");
		fdlist_print(lst->fd_out_err);
		ft_putstr("\n-->\n");
		lst = lst->next;
	}
	ft_putstr("(NULL)");
}

void		list_add_back(void **alst, void *new)
{
	t_cmdlist	*lst;

	lst = *alst;
	if (!lst)
		*alst = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}
