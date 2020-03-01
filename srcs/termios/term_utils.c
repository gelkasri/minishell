
#include "minishell.h"

int		ctrl_key(char c)
{
	if (ft_tolower(c) >= 'a' && ft_tolower(c) <= 'z')
		return (ft_tolower(c) - 96);
	return (-1);
}
