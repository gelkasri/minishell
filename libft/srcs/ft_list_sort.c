/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:09:21 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/24 13:49:16 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	swap_elems(t_list *el1, t_list *el2)
{
	void	*tmp;

	tmp = el1->content;
	el1->content = el2->content;
	el2->content = tmp;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*list_ptr;
	int		changes;

	changes = 0;
	list_ptr = *begin_list;
	if (!list_ptr)
		return ;
	while (list_ptr->next)
	{
		if ((*cmp)(list_ptr->content, list_ptr->next->content) > 0)
		{
			swap_elems(list_ptr, list_ptr->next);
			changes = 1;
		}
		list_ptr = list_ptr->next;
	}
	if (changes)
		ft_list_sort(begin_list, cmp);
}
