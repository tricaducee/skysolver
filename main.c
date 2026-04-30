/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:17 by herolle           #+#    #+#             */
/*   Updated: 2026/04/30 22:35:22 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	pre_compute_lines(unsigned int **tab, unsigned int tab_size)
{
	unsigned int	box;
	unsigned int	i;
	unsigned int	end_i;
	unsigned int	val;

	val = 1;
	while (val <= tab_size)
	{
		box = tab_size - (tab[val][0] - 1);
		i = 1;
		end_i = tab_size - (tab[val][tab_size + 1] - 1);
		while (box < tab_size)
			tab[val][i++] = box++;
		while (i < end_i)
			tab[val][i++] = box;
		while (i <= tab_size)
			tab[val][i++] = box--;
		++val;
	}
}

void	pre_compute_column(unsigned int **tab, unsigned int tab_size)
{
	unsigned int	box;
	unsigned int	i;
	unsigned int	end_i;
	unsigned int	val;

	val = 1;
	while (val <= tab_size)
	{
		box = tab_size - (tab[0][val] - 1);
		i = 1;
		end_i = tab_size - (tab[tab_size + 1][val] - 1);
		while (box < tab_size)
			tab[i++][val] = box++;
		while (i < end_i)
			tab[i++][val] = box;
		while (i <= tab_size)
			tab[i++][val] = box--;
		++val;
	}
}

unsigned int **deepcopy(unsigned int **tab, unsigned int tab_size)
{
	unsigned int	**ret;
	unsigned char	i;
	unsigned char	j;

	ret = malloc(sizeof(unsigned int *) * (tab_size + 3));
	if (!ret)
		return (NULL);
	i = 0;
	while (i <= tab_size + 1)
	{
		ret[i] = malloc(sizeof(unsigned int) * (tab_size + 2));
		if (!ret[i])
			return (free_tab(ret), NULL);
		j = -1;
		while (++j <= tab_size + 1)
			ret[i][j] = tab[i][j];
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	gen_tabs(unsigned int **tab[3], unsigned int tab_size, char **av)
{
	tab[0] = gen_tab(tab_size, av[1]);
	if (!tab[0])
		return (ft_putstr_fd(2, "Error\n"));
	tab[1] = deepcopy(tab[0], tab_size);
	if (!tab[1])
		return (free_tab(tab[0]),ft_putstr_fd(2, "Error\n"));
	tab[2] = deepcopy(tab[0], tab_size);
	if (!tab[2])
		return (free_tab(tab[0]),free_tab(tab[1]),ft_putstr_fd(2, "Error\n"));
	return (0);
}

void	smart_replace_line(unsigned int	**tab, unsigned int **locked_tab, unsigned int tab_size, unsigned int box)
{
	unsigned int		i;
	unsigned int		j;
	const unsigned int	lower_box = box - 1;
	int					count_box;
	unsigned int		unique_i;

	i = 0;
	while (++i <= tab_size)
	{
		if (!(locked_tab[i][tab_size + 2] & (1 << box)))
			continue;
		j = 0;
		count_box = 0;
		unique_i = 0;
		while (++j <= tab_size)
		{
			if (tab[i][j] == box)
			{
				unique_i = j;
				++count_box;
			}
		}
		if (count_box == 1)
		{
			locked_tab[i][unique_i] = box;
			locked_tab[i][tab_size + 2] |= (1 << lower_box);
			locked_tab[tab_size + 2][unique_i] |= (1 << lower_box);
			j = 0;
			while (++j <= tab_size)
			{
				if (tab[j][unique_i] == box && i != j)
					tab[j][unique_i] = lower_box;
			}
		}
	}
}

void	smart_replace_col(unsigned int	**tab, unsigned int **locked_tab, unsigned int tab_size, unsigned int box)
{
	unsigned int		i;
	unsigned int		j;
	const unsigned int	lower_box = box - 1;
	int					count_box;
	unsigned int		unique_i;

	i = 0;
	while (++i <= tab_size)
	{
		if (!(locked_tab[tab_size + 2][i] & (1 << box)))
			continue;
		j = 0;
		count_box = 0;
		unique_i = 0;
		while (++j <= tab_size)
		{
			if (tab[j][i] == box)
			{
				unique_i = j;
				++count_box;
			}
		}
		if (count_box == 1)
		{
			locked_tab[unique_i][i] = box;
			locked_tab[tab_size + 2][i] |= (1 << lower_box);
			locked_tab[unique_i][tab_size + 2] |= (1 << lower_box);
			j = 0;
			while (++j <= tab_size)
			{
				if (tab[unique_i][j] == box && i != j)
					tab[unique_i][j] = lower_box;
			}
		}
	}
}


void	fuse_tabs(unsigned int	**tab[3], unsigned int tab_size)
{
	unsigned int	**col;
	unsigned int	**row;
	unsigned int	i;
	unsigned int	j;

	row = tab[1];
	col = tab[2];
	i = 0;
	while (++i <= tab_size)
	{
		j = 0;
		while (++j <= tab_size)
			row[i][j] = col[i][j] < row[i][j] ? col[i][j] : row[i][j];
	}
}

void	pre_generate(unsigned int **tab[3], unsigned int tab_size)
{
	unsigned int	box;
	pre_compute_lines(tab[1], tab_size);
	pre_compute_column(tab[2], tab_size);
	fuse_tabs(tab, tab_size);
	box = tab_size;
	while (box >= 1)
	{
		smart_replace_col(tab[1], tab[0], tab_size, box);
		smart_replace_line(tab[1], tab[0], tab_size, box);
		box--;
	}
}

void	add_manual_number(unsigned int **tab, t_coor t,
	unsigned int box, unsigned int tab_size)
{
	tab[t.y][t.x] = box;
	tab[tab_size + 2][t.x] |= 1 << (box - 1);
	tab[t.y][tab_size + 2] |= 1 << (box - 1);

}

int	main(int ac, char **av)
{
	unsigned int	tab_size;
	unsigned int	**tab[3];
	t_coor			coor;

	if (ac != 2)
		return (ft_putstr_fd(2, "Error\n"));
	tab_size = check_input(av[1]);
	if (!tab_size)
		return (ft_putstr_fd(2, "Error\n"));
	if (gen_tabs(tab, tab_size, av))
		return (1);
	if (!check_tab(tab[0], tab_size + 2))
		return (ft_putstr_fd(2, "Error\n"));
	pre_generate(tab, tab_size);
	add_manual_number(tab[0], (t_coor){2, 1}, 3, tab_size);
	add_manual_number(tab[0], (t_coor){4, 2}, 5, tab_size);
	add_manual_number(tab[0], (t_coor){7, 1}, 4, tab_size);
	coor.x = 0;
	coor.y = 0;
	#ifdef ANIMATE
		unsigned int	i = 0;
		while (i++ < tab_size + 2)
			write(1, "\n", 1);
	#endif
	if (!sky_solver(tab[0], tab[1], /* new_coor( */coor /*, tab_size, tab[0])*/, tab_size))
		return (ft_putstr_fd(2, "\033[0;31mError\n"));
	else
		print_tab_vu(tab[0], tab_size);
	free_tab(tab[0]);
	free_tab(tab[1]);
	return (0);
}
