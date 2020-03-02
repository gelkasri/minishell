/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:50:12 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 12:04:15 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cmdlist_print(t_cmdlist *lst)
{
	printf("displaying cmdlist:\n");
	while (lst)
	{
		ft_putstr("cmd = ");
		ft_putstr(lst->command);
		ft_putstr(", type = ");
		ft_putnbr(lst->type);
		ft_putstr(", fd = ");
		ft_putnbr(lst->fd);
		printf("cmd = %s, type = %d, fd = %d-->\n",
		lst->command, lst->type, lst->fd);
		lst = lst->next;
	}
	printf("%s\n", "(NULL)");
}

void		cmdlist_add_back(t_cmdlist **alst, t_cmdlist *new)
{
	if (!(*alst))
		*alst = new;
	else
		cmdlist_last(*alst)->next = new;
}

t_cmdlist	*cmdlist_last(t_cmdlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void		cmdlist_set(t_cmdlist *item, char *cmd, int type, int fd)
{
	if ((int)cmd != -42)
		item->command = cmd;
	if (type != -42)
		item->type = type;
	if (fd != -42)
		item->fd = fd;
}
