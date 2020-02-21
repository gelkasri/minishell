/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:01:57 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 22:14:12 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			**init_env_list(char **envp)
{
	int		i;
	t_list	**list;

	if (!(list = ft_memalloc(sizeof(t_list *))))
		return (NULL);
	i = 0;
	while (envp[i])
		ft_lstadd_back(list, ft_lstnew(ft_strdup(envp[i++])));
	return (list);
}

char			*get_env_var(const char *var, t_list **env_list)
{
	t_list	*env;
	char	**split;
	char	*res;
	char	*join;

	if (!(join = ft_strjoin(var, "=")))
		return (NULL);
	env = *env_list;
	while (env)
	{
		if (ft_strstr(env->content, join) == env->content)
		{
			if (!(split = ft_split(env->content, '=')))
				return (NULL);
			if (!(res = ft_strdup(split[1])))
				return (NULL);
			free_str_arr(split);
			free(split);
			free(join);
			return (res);
		}
		env = env->next;
	}
	free(join);
	return (NULL);
}

static void		new_env_var(const char *var, const char *value, t_list **env_l)
{
	(void)env_l;
	ft_printf("Add new environement variable : %s=%s\n", var, value);
}

void			set_env_var(const char *var, const char *value, t_list **env_l)
{
	if (get_env_var(var, env_l))
	{
		return ;
	}
	else
	{
		new_env_var(var, value, env_l);
	}
}
