/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:42:22 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/26 09:04:21 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static char	*replace_at_pos(char *str, int pos, int oldlen, char *var)
{
	char	*new;
	int		new_pos;

	new = ft_memalloc(ft_strlen(str) - oldlen + 1 + ft_strlen(var));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	ft_strncpy(new, str, pos);
	ft_strcpy(new + pos, var);
	new_pos = pos + ft_strlen(var);
	ft_strcpy(new + new_pos, str + pos + oldlen);
	free(str);
	return (new);
}

static char	*replace_env_var(char *str, int index, t_list **env_list)
{
	int		i;
	char	*ret;
	char	*substr;
	char	*var;

	i = index + 1;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]))
		i++;
	if (i == index + 1)
		return (str);
	substr = ft_substr(str, index + 1, i - (index + 1));
	var = get_env_var(substr, env_list);
	if (!var)
		var = ft_strdup("");
	ret = replace_at_pos(str, index, ft_strlen(substr) + 1, var);
	free(var);
	free(substr);
	if (!ret)
		return (NULL);
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
		{
			if (ft_isalpha(str[i + 1]) || ft_isdigit(str[i + 1]))
				return (i);
		}
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
	while ((last_index = get_next_match(final)) != -1)
	{
		final = replace_env_var(final, last_index, env_list);
		if (!final)
			return (ft_strdup(""));
	}
	return (final);
}
