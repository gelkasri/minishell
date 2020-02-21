/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 03:18:01 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/10 11:43:30 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcapitalize(char *str)
{
	int		diff;
	int		i;

	i = 0;
	diff = 'A' - 'a';
	str[0] = (str[0] >= 'a' && str[0] <= 'z') ? str[i] + diff : str[i];
	while (str[++i])
	{
		if (!ft_isalnum(str[i - 1]))
			str[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] + diff : str[i];
		else
			str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] - diff : str[i];
	}
	return (str);
}
