/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:43:53 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/27 11:56:32 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this list_free doesn't free el->content
*/

static void		special_list_free(t_list *list)
{
	t_list	*el_to_free;

	while (list)
	{
		el_to_free = list;
		list = list->next;
		free(el_to_free);
	}
}

static t_list	*ft_list_cp_sort(t_list *list)
{
	t_list	*new_list;
	t_list	*new_el;

	new_list = NULL;
	while (list)
	{
		new_el = ft_lstnew(list->content);
		if (!new_el)
		{
			special_list_free(new_list);
			return (NULL);
		}
		ft_lstadd_front(&new_list, new_el);
		list = list->next;
	}
	ft_list_sort(&new_list, ft_strcmp);
	return (new_list);
}

static int		print_list(t_list *list)
{
	char	**split;

	while (list)
	{
		split = split_in_2(list->content, '=');
		if (!split)
			return (1);
		if (!ft_strcmp(split[0], "?"))
		{
			list = list->next;
			continue ;
		}
		ft_putstr(split[0]);
		if (split[1] && ft_strcmp(split[1], ""))
		{
			ft_putstr("=\"");
			ft_putstr(split[1]);
			ft_putstr("\"");
		}
		ft_putstr("\n");
		free_str_arr(split);
		free(split);
		list = list->next;
	}
	return (0);
}

int				export_no_param(t_list **env_list)
{
	t_list	*copy_sorted;
	int		ret;

	copy_sorted = ft_list_cp_sort(*env_list);
	if (!copy_sorted)
	{
		ft_putendl_fd("export: malloc failed", 2);
		return (1);
	}
	ret = print_list(copy_sorted);
	if (ret)
		ft_putendl_fd("export: malloc failed", 2);
	special_list_free(copy_sorted);
	return (ret);
}
