#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "sky_solver.h"

void	sky_editor(t_all *all)
{
	struct termios	old_term;
	struct termios	new_term;
	t_coor			coor;
	char			c;
	unsigned int	n;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ECHO | ICANON);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);
	coor.x = 1;
	coor.y = 0;
	while (1)
	{
		ft_putstr_fd(1, "'enter' for begin, arrows for select value to change with num\n");
		print_tab_vu_coor(all->map, coor, all->tab_size);
		read(STDIN_FILENO, &c, 1);
		if (c == '\n')
			break ;
		else if (c <= '9' && c >= '0')
		{
			n = c - '0';
			if (n <= all->tab_size)
				add_manual_number(all->map, coor, c - '0', all->tab_size);
		}
		else if (c == '\033')
		{
			read(STDIN_FILENO, &c, 1);
			if (c == '[')
			{
				read(STDIN_FILENO, &c, 1);
				switch (c)
				{
					case 'A': // Haut
						if (coor.x != 0 && coor.x != all->tab_size + 1)
						{
							if (coor.y > 0)
								coor.y--;
							else
								coor.y = all->tab_size + 1;
						} else {
							if (coor.y > 1)
								coor.y--;
							else
								coor.y = all->tab_size;
						}
						break;
					case 'B': // Bas
						if (coor.x != 0 && coor.x != all->tab_size + 1)
						{
							if (coor.y < all->tab_size + 1)
								coor.y++;
							else
								coor.y = 0;
						} else {
							if (coor.y < all->tab_size)
								coor.y++;
							else
								coor.y = 1;
						}
						break;
					case 'C': // Droite
						if (coor.y != 0 && coor.y != all->tab_size + 1)
						{
							if (coor.x < all->tab_size + 1)
								coor.x++;
							else
								coor.x = 0;
						} else {
							if (coor.x < all->tab_size)
								coor.x++;
							else
								coor.x = 1;
						}
						break;
					case 'D': // Gauche
						if (coor.y != 0 && coor.y != all->tab_size + 1)
						{
							if (coor.x > 0)
								coor.x--;
							else
								coor.x = all->tab_size + 1;
						} else {
							if (coor.x > 1)
								coor.x--;
							else
								coor.x = all->tab_size;
						}
						break;
				}
			}
		}
		up_lines(all->tab_size + 3);
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_term);
}