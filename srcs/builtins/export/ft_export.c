/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:39:53 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/06 17:12:19 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_chars(const char *str)
{
	int	i;
	int	char_is_ok;

	i = 0;
	while (str[i])
	{
		char_is_ok = ft_isdigit(str[i]) || ft_isalpha(str[i]);
		if (!char_is_ok && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int			check_errors(const char *str, const char *name,
const char *error_param)
{
	if (!str[0] || ft_isdigit(str[0]) || !check_chars(str))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name, 2);
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
** var KEY is set if there is no env var named KEY OR =VALUE is given
*/

int			parse_and_export(char *str, t_list **env_list)
{
	char	**split;
	char	*old_value;

	if (str[0] == '=')
		return (check_errors("", "export: `", str));
	if (!(split = split_in_2(str, '=')))
		return (1);
	if (check_errors(split[0], "export: `", str))
	{
		free_str_arr(split);
		free(split);
		return (1);
	}
	if (!(old_value = get_env_var(split[0], env_list)) || split[1])
	{
		if (split[0] && split[1])
			set_env_var(split[0], split[1], env_list);
		else if (split[0])
			set_env_var(split[0], "", env_list);
	}
	free_str_arr(split);
	free(split);
	free(old_value);
	return (0);
}

/*
** ft_export sets the environment variables with all strings in char **av
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
