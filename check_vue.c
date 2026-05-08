/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:27:39 by herolle           #+#    #+#             */
/*   Updated: 2026/05/08 21:32:07 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"

// int	check_min_index(unsigned int **tab, t_coor coor,
// 	unsigned int tab_size, unsigned int box)
// {
// 	int	diff;
// 	int	result;

// 	diff = tab_size - box;
// 	result = tab[coor.y + 1][0] - diff - 1;
// 	if ((int)coor.x < result)
// 		return (0);
// 	result = tab[0][coor.x + 1] - diff - 1;
// 	return (!((int)coor.y < result));
// }

int	check_min_index(unsigned int **tab, t_coor coor, unsigned int box)
{
	return (box <= tab[coor.y][coor.x]);
}

int	check_vue_column(unsigned int **tab,
	t_coor coor, unsigned int tab_size)
{
	t_coor			index;
	unsigned int	vue;
	unsigned int	max_size;

	index.x = coor.x;
	index.y = 0;
	vue = 1;
	max_size = tab[index.y + 1][coor.x];
	while (index.y < coor.y - 1)
	{
		++index.y;
		if (tab[index.y + 1][coor.x] > max_size)
		{
			max_size = tab[index.y + 1][coor.x];
			++vue;
		}
	}
	if (vue > tab[0][coor.x]
		|| (coor.y == tab_size && vue != tab[0][coor.x]))
		return (0);
	return (1);
}

int	check_vue_line(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	t_coor			index;
	unsigned int	vue;
	unsigned int	max_size;

	index.x = 0;
	index.y = coor.y;
	vue = 1;
	max_size = tab[coor.y][index.x + 1];
	while (index.x < coor.x - 1)
	{
		++index.x;
		if (tab[coor.y][index.x + 1] > max_size)
		{
			max_size = tab[coor.y][index.x + 1];
			++vue;
		}
	}
	if (vue > tab[coor.y][0]
		|| (coor.x == tab_size && vue != tab[coor.y][0]))
		return (0);
	return (1);
}

int	check_vue_column_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	t_coor			index;
	unsigned int	vue;
	unsigned int	max_size;

	if (coor.y != tab_size)
		return (1);
	index.x = coor.x;
	index.y = coor.y;
	vue = 1;
	max_size = tab[coor.y][coor.x];
	while (index.y - 1 > 0)
	{
		--index.y;
		if (tab[index.y][index.x] > max_size)
		{
			max_size = tab[index.y][index.x];
			++vue;
		}
	}
	if (vue != tab[tab_size + 1][coor.x])
		return (0);
	return (1);
}

int	check_vue_line_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	t_coor			index;
	unsigned int	vue;
	unsigned int	max_size;

	if (coor.x != tab_size)
		return (1);
	index.x = coor.x;
	index.y = coor.y;
	vue = 1;
	max_size = tab[coor.y][coor.x];
	while (index.x - 1 > 0)
	{
		--index.x;
		if (tab[index.y][index.x] > max_size)
		{
			max_size = tab[index.y][index.x];
			++vue;
		}
	}
	if (vue != tab[coor.y][tab_size + 1])
		return (0);
	return (1);
}

// int	check_vue_line_rev(unsigned int **tab,
// 		t_coor coor, unsigned int tab_size)
// {
// 	t_coor			index;
// 	unsigned int	vue;
// 	unsigned int	max_size;

// 	index.x = coor.x;
// 	index.y = coor.y;
// 	vue = 1;
// 	max_size = tab[coor.y + 1][coor.x + 1];
// 	while (index.x > 0)
// 	{
// 		--index.x;
// 		if (tab[index.y + 1][index.x + 1] > max_size)
// 		{
// 			max_size = tab[index.y + 1][index.x + 1];
// 			++vue;
// 		}
// 	}
// 	if (vue > tab[coor.y + 1][tab_size + 1]
// 		|| (coor.x == tab_size - 1 && vue
//		!= tab[coor.y + 1][tab_size + 1]))
// 		return (0);
// 	return (1);
// }
