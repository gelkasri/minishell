/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:42:22 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/25 19:10:41 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

//use trim_this_part !!??

static char	*replace_env_var(char *str, int index, t_list **env_list)
{
	int		i;
	char	*ret;
	char	*substr;
	char	*test;

	printf("--------------------------\n");
	i = index + 1;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]))
		i++;
	substr = ft_substr(str, index + 1, i - (index + 1));
	printf("substr = %s\n", substr);
	test = get_env_var(substr, env_list);
	printf("env_var = %s\n", test);
	free(test);
	free(substr);
	ret = ft_strdup(str);
	free(str);
	printf("--------------------------\n");
	return (ret);
}

static int	get_next_match(char *str)
{
	int		i;
	int		in_quote;
	int		in_dquote;

	in_quote = 0;
	in_dquote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !in_quote)
			in_dquote = (in_dquote + 1) % 2;
		else if (str[i] == '\'' && !in_dquote)
			in_quote = (in_quote + 1) % 2;
		else if (str[i] == '$' && !in_quote)
			return (i);
		i++;
	}
	return (-1);
}

/*
** do not free str
** it is freed in exec_line: 90
*/

char		*apply_env_var(char *str, t_list **env_list)
{
	char	*final;
	int		last_index;

	last_index = 0;
	if (ft_strlen(str) == 0)
	{
		free(str);
		return (NULL);
	}
	final = ft_strdup(str);
	if (!final)
		return (NULL);
	// mettre un while
	if ((last_index = get_next_match(final)) != -1)
	{
		final = replace_env_var(final, last_index, env_list);
		if (!final)
			return (NULL);
	}
	return (final);
}
