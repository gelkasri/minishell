/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:17:24 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/21 14:24:59 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** on pourra remplacer par la fonction strcmp de la libft
*/

int		ft_strcmp(char *s1, char *s2)
{
	int i;
	int diff;

	diff = 0;
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		diff = s1[i] - s2[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	return (0);
}

/*
** on pourra remplacer par la fonction put_str ou ft_putstr_fd de la libft
*/

void	ft_putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		i++;
	write(fd, str, i);
}

int		get_n_option(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp("-n", str) == 0)
		return (1);
	return (0);
}

int		ft_echo(int ac, char **av)
{
	int	n_option;
	int	i;

	n_option = 0;
	if (ac > 1)
		n_option = get_n_option(av[1]);
	i = 1;
	if (n_option)
		i = 2;
	while (i < ac)
	{
		ft_putstr_fd(av[i], 1);
		i++;
		if (i < ac)
			write(1, " ", 1);
	}
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
