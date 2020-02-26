/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:01:57 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/26 12:28:55 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Allocate and init a chained list containing environement variables
** - envp = environement variables array (as passed in main)
**
** Return value :
** - Pointer to the first item in the list
** - NULL if malloc error
*/

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

/*
** Allocate and fill an array with all environement variabes
**     format: VAR=VALUE
** - env_list = environement variables list
**
** Return value :
** - NULL-terminated array with all environement variables
** - NULL if env_list is null or empty, and in case of malloc error
*/

char			**get_env_array(t_list **env_list)
{
	t_list	*elem;
	int		len;
	char	**res;
	int		i;

	if (!env_list || !(*env_list))
		return (NULL);
	len = ft_lstsize(*env_list);
	if (!(res = ft_memalloc((len + 1) * sizeof(char *))))
		return (NULL);
	elem = *env_list;
	i = 0;
	while (elem)
	{
		res[i] = ft_strdup(elem->content);
		elem = elem->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

static void		multi_free(char ***array_ptr, char **str_ptr)
{
	if (array_ptr && *array_ptr)
	{
		free_str_arr(*array_ptr);
		free(*array_ptr);
	}
	if (str_ptr)
		free(*str_ptr);
}

char			*get_env_var(const char *var, t_list **env_list)
{
	t_list	*env;
	char	**split;
	char	*res;
	char	*join;
	int		empty_arg;

	if (!(join = ft_strjoin(var, "=")))
		return (NULL);
	env = *env_list;
	while (env)
	{
		if (ft_strstr(env->content, join) == env->content)
		{
			if (!(split = split_in_2(env->content, '=')))
				return (NULL);
			if (split[1] && !(res = ft_strdup(split[1])))
				return (NULL);
			empty_arg = split[1] ? 0 : 1;
			multi_free(&split, &join);
			return (empty_arg ? ft_strdup("") : res);
		}
		env = env->next;
	}
	free(join);
	return (NULL);
}

void			set_env_var(const char *var, const char *value, t_list **env_l)
{
	char	*new_var;
	t_list	*elem;
	char	*join;
	char	*old_var;

	elem = *env_l;
	new_var = ft_strjoin3(var, "=", value);
	join = ft_strjoin(var, "=");
	if (join && (old_var = get_env_var(var, env_l)))
	{
		while (elem)
		{
			if (ft_strstr(elem->content, join) == elem->content)
			{
				free(elem->content);
				elem->content = new_var;
				break ;
			}
			elem = elem->next;
		}
		free(old_var);
	}
	else if (new_var)
		ft_lstadd_back(env_l, ft_lstnew(new_var));
	free(join);
}
