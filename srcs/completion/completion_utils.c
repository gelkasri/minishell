/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:37:52 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/06 10:58:19 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

char	*get_name(struct dirent *file)
{
	char	*ret;

	if (file->d_type == DT_DIR)
	{
		ret = ft_memalloc(ft_strlen(file->d_name + 2));
		if (!ret)
			return (NULL);
		ft_strcpy(ret, file->d_name);
		ft_strcat(ret, "/");
	}
	else
		ret = ft_strdup(file->d_name);
	return (ret);
}

int		case_unsensitive_ncmp(const char *s1, const char *s2, size_t n)
{
	int i;

	if (!n)
		return (0);
	i = 0;
	while (ft_tolower(s1[i]) == ft_tolower(s2[i])
	&& s1[i] != '\0' && i < (int)(n - 1))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
