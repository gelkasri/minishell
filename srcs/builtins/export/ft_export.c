/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:39:53 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/24 14:24:02 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_is_alpha_num(const char *str)
{
	int	i;
	int	char_is_ok;

	i = 0;
	while (str[i])
	{
		char_is_ok = ft_isdigit(str[i]) || ft_isalpha(str[i]);
		if (!char_is_ok)
			return (0);
		i++;
	}
	return (1);
}

static int	check_errors(const char *str, const char *error_param)
{
	if (!str[0] || ft_isdigit(str[0]) || !ft_str_is_alpha_num(str))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(error_param, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

/*
** parse_and_export takes a string formatted as follow:
** KEY[=VALUE]
** (=VALUE is facultative)
*/

int			parse_and_export(char *str, t_list **env_list)
{
	char	**split;

	if (str[0] == '=')
		return (check_errors("", str));
	split = ft_split(str, '=');
	if (!split)
		return (1);
	if (check_errors(split[0], str))
	{
		free_str_arr(split);
		free(split);
		return (1);
	}
	if (split[0] && split[1])
		set_env_var(split[0], split[1], env_list);
	else if (split[0])
		set_env_var(split[0], "", env_list);
	free_str_arr(split);
	free(split);
	return (0);
}

/*
** ft_export set the environment variables with all strings in char **av
** if ac=1, it displays the environment variables
*/

int			ft_export(int ac, char **av, t_list **env_list)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (ac == 1)
		return (export_no_param(env_list));
	while (ac > i)
	{
		ret |= parse_and_export(av[i], env_list);
		i++;
	}
	return (ret);
}
