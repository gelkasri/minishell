/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:50:12 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 18:04:23 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fdlist	*fdlist_new(int fd)
{
	t_fdlist	*new;

	new = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void		fdlist_clear(t_fdlist **lst)
{
	t_fdlist	*temp;
	t_fdlist	*iter;

	if (!lst || !(*lst))
		return ;
	iter = *lst;
	while (iter)
	{
		temp = iter->next;
		close(iter->fd);
		free(iter);
		iter = temp;
	}
	*lst = NULL;
	lst = NULL;
}

void		fdlist_print(t_fdlist *lst)
{
	while (lst)
	{
		ft_putnbr(lst->fd);
		ft_putstr("-->\n");
		lst = lst->next;
	}
	ft_putstr("(NULL)\n");
}
