/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 01:25:26 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/10 14:16:59 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *res;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	tmp = ft_lstnew(f(lst->content));
	res = tmp;
	while (lst->next)
	{
		if (!(tmp->next = ft_lstnew(f(lst->next->content))))
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		del(lst->content);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (res);
}
