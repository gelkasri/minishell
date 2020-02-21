/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 01:40:50 by gel-kasr          #+#    #+#             */
/*   Updated: 2019/11/16 06:24:40 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cut_buf(char **pos, char *temp, char *buf, char **line)
{
	char	*substr;
	int		index;

	if (!(substr = (char *)ft_memalloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	index = (ft_index(*pos, '\n') >= 0) ? ft_index(*pos, '\n')
										: ft_index(buf, '\n');
	ft_memmove(substr, buf, index);
	ft_strlcat(temp, substr, ft_strlen(*line) + BUFFER_SIZE + 1);
	ft_memmove(*pos, buf + index + 1, BUFFER_SIZE - index);
	free(substr);
	return (1);
}

static int	read_buf(char *buf, char **line, char **pos, int read_size)
{
	char	*temp;
	int		res;
	int		index;

	if (!(temp = ft_memalloc((ft_strlen(*line) + BUFFER_SIZE + 1)
								* sizeof(char))))
		return (-1);
	buf[(read_size < BUFFER_SIZE) ? read_size : BUFFER_SIZE] = 0;
	ft_strlcat(temp, *line, ft_strlen(*line) + 1);
	if ((index = ft_index(buf, '\n')) < 0)
	{
		ft_strlcat(temp, buf, ft_strlen(*line) + BUFFER_SIZE + 1);
		res = 0;
	}
	else
	{
		res = cut_buf(pos, temp, buf, line);
	}
	free(*line);
	*line = temp;
	return (res);
}

static int	read_pos(char **line, char **pos, int index, char *buf)
{
	ft_memmove(*line, *pos, index);
	*(*line + index) = 0;
	ft_memmove(*pos, *pos + index + 1, ft_strlen(*pos) - index);
	free(buf);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char			*buf;
	int				index;
	int				read_size;
	static char		*pos = NULL;

	if (!pos && !(pos = (char *)ft_memalloc(sizeof(*pos) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!(*line = ft_memalloc((BUFFER_SIZE + 1) * sizeof(char))) || fd < 0 ||
		!(buf = malloc((BUFFER_SIZE + 1) * sizeof(char))) || BUFFER_SIZE <= 0)
		return (-1);
	if ((index = ft_index(pos, '\n')) >= 0)
		return (read_pos(line, &pos, index, buf));
	ft_strlcat(*line, pos, ft_strlen(pos) + 1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if ((read_size = read_buf(buf, line, &pos, read_size)))
		{
			free(buf);
			return ((read_size < 0) ? -1 : 1);
		}
	}
	free(pos);
	pos = NULL;
	free(buf);
	return ((read_size < 0) ? -1 : 0);
}
