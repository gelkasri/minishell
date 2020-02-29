
#include "minishell.h"
#include <termios.h>

/*
** Return current cursor position. 
** Write position in a buffer, format <ESC>[10;15R
*/

t_coord		get_cur_pos(void)
{
	char			buf[30]={0};
	int				i, pow;
	struct termios	term;
	struct termios	restore;
	t_coord c;
	
	c = (t_coord){0, 0};
	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(0, TCSANOW, &term);
	write(0, "\033[6n", 4);
	i = 0;
	while (i == 0 || buf[i - 1] != 'R')
		read(0, &buf[i++], 1);
	i -= 2;
	pow = 1;
	while (buf[i] != ';')
	{
		c.x = c.x + (buf[i--] - '0') * pow;
		pow *= 10;
	}
	i--;
	pow = 1;
	while (buf[i] != '[')
	{
		c.y = c.y + (buf[i--] - '0' ) * pow;
		pow *= 10;
	}
	tcsetattr(0, TCSANOW, &restore);
	return (c);
}
