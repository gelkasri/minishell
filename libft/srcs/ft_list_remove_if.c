/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 09:34:36 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/24 15:31:26 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	rm_el(t_list *last, t_list **el, void (*free_fct)(void *))
{
	if (last)
		last->next = (*el)->next;
	(*free_fct)((*el)->content);
	free((*el));
	*el = 0;
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
void (*free_fct)(void *))
{
	t_list	*list_ptr;
	t_list	*last;
	t_list	*tmp;
	int		first;

	first = 1;
	list_ptr = *begin_list;
	last = 0;
	while (list_ptr)
	{
		tmp = list_ptr->next;
		if ((*cmp)(list_ptr->content, data_ref) == 0)
		{
			if (first)
				(*begin_list) = list_ptr->next;
			rm_el(last, &list_ptr, free_fct);
		}
		else
			first = 0;
		if (list_ptr)
			last = list_ptr;
		list_ptr = tmp;
	}
}
