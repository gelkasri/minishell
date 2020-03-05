/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:41:57 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/05 17:44:37 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "fcntl.h"
#include "string.h"
#include "errno.h"

static void	print_history(t_history *history)
{
	int		line_no;
	t_list	*list;

	list = history->list;
	line_no = (history->ln_no > 500) ? history->ln_no - 501 : 1;
	while (list)
	{
		ft_printf("%5d  %s\n", line_no++, list->content);
		list = list->next;
	}
}

static int	fd_error(char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(error, 2);
	return (1);
}

static int	quit_ft_history(t_history *history, int ret_val)
{
	close(history->fd);
	if (history->list)
		print_history(history);
	ft_lstclear(&(history->list), free);
	return (ret_val);
}

static int	read_lines(t_history *history)
{
	while (get_next_line(history->fd, &(history->line)) > 0)
	{
		if (history->ln_no++ > 500)
		{
			free(history->line);
			continue ;
		}
		history->new = ft_lstnew(history->line);
		if (!history->new)
		{
			free(history->line);
			return (quit_ft_history(history, 1));
		}
		ft_lstadd_front(&(history->list), history->new);
	}
	free(history->line);
	return (0);
}

int			ft_history(int ac, char **av, t_list **env_list)
{
	t_history	history;
	int			err;

	(void)ac;
	(void)av;
	history.ln_no = 1;
	history.list = NULL;
	history.file_path = get_histo_file_path(env_list);
	if (!history.file_path)
		return (MALLOC_ERROR);
	history.fd = open(history.file_path, O_RDONLY);
	free(history.file_path);
	if (history.fd < 0)
		return (quit_ft_history(&history, fd_error(HISTO_FILE_ERR)));
	err = read_lines(&history);
	if (err)
		return (err);
	return (quit_ft_history(&history, 0));
}
