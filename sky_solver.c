/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:34 by herolle           #+#    #+#             */
/*   Updated: 2026/04/28 12:15:50 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"
#include <unistd.h>

int	is_end(t_coor coor, unsigned int tab_size)
{
	if (!(coor.x + 1 < tab_size) && !(coor.y + 1 < tab_size))
		return (1);
	return (0);
}

t_coor	new_coor(t_coor coor, unsigned int tab_size)
{
	if (coor.x + 1 < tab_size)
		++coor.x;
	else if (coor.y + 1 < tab_size)
	{
		coor.x = 0;
		++coor.y;
	}
	return (coor);
}

int	check_column_and_line_bit_shift(unsigned int **tab, t_coor coor, unsigned int tab_size, unsigned int box)
{
	const unsigned int	i = (1 << (box - 1));
	const unsigned int	delta = tab_size + 2;

	if (!(tab[delta][coor.x + 1] & i) && !(tab[coor.y + 1][delta] & i))
	{
		tab[delta][coor.x + 1] |= i;
		tab[coor.y + 1][delta] |= i;
		return (1);
	}
	return (0);
}

int	check_column_and_line(unsigned int **tab, t_coor coor, unsigned int box)
{
	t_coor	index;

	index.x = coor.x;
	index.y = 0;
	while (index.y < coor.y)
	{
		if (tab[index.y + 1][index.x + 1] == box)
			return (0);
		++index.y;
	}
	index.x = 0;
	index.y = coor.y;
	while (index.x < coor.x)
	{
		if (tab[index.y + 1][index.x + 1] == box)
			return (0);
		++index.x;
	}
	return (1);
}

// Bmin = C <= Tx + y

// Bmax = tab_size

unsigned int	check_visibility_min(unsigned int **tab, t_coor coor,
	unsigned int tab_size, unsigned int box)
{
	t_coor	index;

	index.x = coor.x + 1;
	index.y = coor.y + 1;
	int	min_i = ((int)tab[0][index.x] - (int)((int)tab_size - (int)box)) - 1;
	return (min_i < 0 || index.y > (unsigned int)min_i);
}

unsigned int	put_box(unsigned int **tab, t_coor coor,
	unsigned int tab_size, unsigned int box)
{
	t_coor	boxes_save;
	while (1)
	{
		boxes_save.x = tab[tab_size + 2][coor.x + 1];
		boxes_save.y = tab[coor.y + 1][tab_size + 2];
		tab[coor.y + 1][coor.x + 1] = box;
		if (
			//check_visibility_min(tab, coor, tab_size, box)
			check_column_and_line_bit_shift(tab, coor, tab_size, box)
			&& check_min_index(tab, coor, tab_size, box)
			&& check_vue_column(tab, coor, tab_size)
			&& check_vue_column_rev(tab, coor, tab_size)
			&& check_vue_line(tab, coor, tab_size)
			&& check_vue_line_rev(tab, coor, tab_size))
			return (box);
		++box;
		tab[tab_size + 2][coor.x + 1] = boxes_save.x;
		tab[coor.y + 1][tab_size + 2] = boxes_save.y;
		if (box > tab_size)
			break ;
	}
	return (0);
}

int	sky_solver(unsigned int	**tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	box;
	t_coor			boxes_save;
	int				ret;

	box = 1;
	while (1)
	{
		boxes_save.x = tab[tab_size + 2][coor.x + 1];
		boxes_save.y = tab[coor.y + 1][tab_size + 2];
		box = put_box(tab, coor, tab_size, box);
		if (!box)
		{
			tab[coor.y + 1][coor.x + 1] = 0;
			return (0);
		}
		#ifdef ANIMATE
			up_lines(tab_size + 2);
		#endif
		if (is_end(coor, tab_size))
			return (1);
		#ifdef ANIMATE
			print_tab_vu(tab, tab_size);
		#endif
		ret = sky_solver(tab, new_coor(coor, tab_size), tab_size);
		if (ret)
			return (ret);
		tab[tab_size + 2][coor.x + 1] = boxes_save.x;
		tab[coor.y + 1][tab_size + 2] = boxes_save.y;
		++box;
		if (box > tab_size)
		{
			tab[coor.y + 1][coor.x + 1] = 0;
			return (0);
		}
	}
	return (ret);
}
