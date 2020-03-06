/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:57:18 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/06 16:25:00 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	content_cmp(void *content, void *reference)
{
	if (ft_strstr(content, reference) == content)
		return (0);
	return (1);
}

int			ft_unset(int ac, char **av, t_list **env_list)
{
	int		i;
	int		ret;
	char	*join;

	ret = 0;
	i = 1;
	if (ac == 1)
		return (0);
	while (ac > i)
	{
		join = ft_strjoin(av[i], "=");
		if (!join)
			return (1);
		if (check_errors(av[i], "unset: `", av[i]))
			ret = 1;
		else
			ft_list_remove_if(env_list, join, content_cmp, free);
		free(join);
		i++;
	}
	return (ret);
}
