/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:33:29 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 15:44:14 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr(char **to_free)
{
	int	i;

	if (!to_free)
		return ;
	i = 0;
	while (to_free[i])
		free(to_free[i++]);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char			*res;

	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	res = (char *)malloc(sizeof(*res) *
						(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcat(res, s2);
	ft_strcat(res, s3);
	return (res);
}
