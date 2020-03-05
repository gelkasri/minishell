/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:12:17 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/05 16:54:15 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_char_ok(char c)
{
	if (!c || ft_isspace(c) || c == '/')
		return (1);
	return (0);
}

static char	*replace_char_here(char *str, int index, char *new)
{
	int		ok;
	char	*final;

	if (!new)
		return (free_return(str, new, NULL));
	ok = 0;
	if (index == 0 && (!str[1] || ft_isspace(str[1] || str[1] == '/')))
		ok = 1;
	if (index != 0 && ft_isspace(str[index - 1]) &&
		next_char_ok(str[index + 1]))
		ok = 1;
	if (!ok)
		return (free_return(new, NULL, str));
	final = ft_memalloc(ft_strlen(str) + ft_strlen(new));
	if (!final)
		return (free_return(str, new, NULL));
	ft_strncpy(final, str, index);
	ft_strcat(final, new);
	ft_strcat(final, str + index + 1);
	return (free_return(str, new, final));
}

char		*replace_tilde(char *str, t_list **env_list)
{
	int		i;
	int		quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !quote[1])
			quote[0] = (quote[0] + 1) % 2;
		else if (str[i] == '\'' && !quote[0])
			quote[1] = (quote[1] + 1) % 2;
		else if (str[i] == '~' && !quote[0] && !quote[1])
		{
			if (!(str = replace_char_here(str, i,
			get_env_var("HOME", env_list))))
				return (NULL);
		}
		i++;
	}
	return (str);
}
