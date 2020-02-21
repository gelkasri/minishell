/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:26:07 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 14:52:12 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char	**line;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	if (!(line = ft_memalloc(sizeof(char *))))
		return (MALLOC_ERROR);
	ft_printf("%sBienvenue dans Minishell%s\n\n", GREEN, WHITE);
	while (1)
	{
		*line = NULL;
		display_prompt(envp);
		i = get_next_line(0, line);
		if (i <= 0)
			break ;
		exec_line(*line, envp);
		free(*line);
	}
	if (*line)
		free(*line);
	free(line);
	return (0);
}
