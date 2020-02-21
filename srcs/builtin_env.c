/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:01:57 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 19:26:28 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*get_env_var(const char *var, char **envp)
{
	int		i;
	char	**split;
	char	*res;
	char	*join;

	i = 0;
	if (!(join = ft_strjoin(var, "=")))
		return (NULL);
	while (envp[i])
	{
		if (ft_strstr(envp[i], join) == envp[i])
		{
			if (!(split = ft_split(envp[i], '=')))
				return (NULL);
			if (!(res = ft_strdup(split[1])))
				return (NULL);
			free_str_arr(split);
			free(split);
			free(join);
			return (res);
		}
		i++;
	}
	free(join);
	return (NULL);
}

static void		new_env_var(const char *var, const char *value, char ***envp)
{
	(void)envp;
	ft_printf("Add new environement variable : %s=%s\n", var, value);
}

void			set_env_var(const char *var, const char *value, char ***envp)
{
	if (get_env_var(var, *envp))
	{
		return ;
	}
	else
	{
		new_env_var(var, value, envp);
	}
}
