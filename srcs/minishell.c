/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:26:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/22 16:56:06 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	main_loop(char **line, t_list **env_list)
{
	int		i;
	char	*res;

	while (1)
	{
		*line = NULL;
		display_prompt(env_list);
		i = get_next_line(0, line);
		if (i <= 0)
			break ;
		i = exec_line(*line, env_list);
		res = ft_itoa(i);
		set_env_var("?", res, env_list);
		free(*line);
		free(res);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	char	**line;
	t_list	**env_list;

	(void)argc;
	(void)argv;
	if (!(env_list = init_env_list(envp)))
		return (MALLOC_ERROR);
	if (!(line = ft_memalloc(sizeof(char *))))
		return (MALLOC_ERROR);
	ft_printf("%sBienvenue dans Minishell%s\n\n", GREEN, WHITE);
	main_loop(line, env_list);
	if (*line)
		free(*line);
	free(line);
	return (0);
}
