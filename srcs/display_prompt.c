/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:15:04 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/07 11:34:56 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(t_list **env_list)
{
	char *color;
	char *res;

	res = get_env_var("?", env_list);
	if (!res)
		color = BLUE;
	else if (ft_atoi(res))
		color = RED;
	else
		color = GREEN;
	ft_printf("%s%3s - bébéshell> %s", color, res, WHITE);
	free(res);
}
