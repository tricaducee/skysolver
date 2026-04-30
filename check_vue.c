/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herolle <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:27:39 by herolle           #+#    #+#             */
/*   Updated: 2024/09/01 17:27:41 by herolle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"

int	check_min_index(unsigned int **tab, t_coor coor,
	unsigned int tab_size, unsigned int box)
{
	int	diff;
	int	result;

	diff = tab_size - box;
	result = tab[coor.y + 1][0] - diff - 1;
	if (result > 0 && result > (int)coor.x)
		return (0);
	result = tab[0][coor.x + 1] - diff - 1;
	if (result > 0 && result > (int)coor.y)
		return (0);
	return (1);
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
	max_size = tab[index.y + 1][index.x + 1];
	while (index.y < coor.y)
	{
		++index.y;
		if (tab[index.y + 1][index.x + 1] > max_size)
		{
			max_size = tab[index.y + 1][index.x + 1];
			++vue;
		}
	}
	if (vue > tab[0][coor.x + 1]
		|| (coor.y == tab_size - 1 && vue != tab[0][coor.x + 1]))
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
	max_size = tab[index.y + 1][index.x + 1];
	while (index.x < coor.x)
	{
		++index.x;
		if (tab[index.y + 1][index.x + 1] > max_size)
		{
			max_size = tab[index.y + 1][index.x + 1];
			++vue;
		}
	}
	if (vue > tab[coor.y + 1][0]
		|| (coor.x == tab_size - 1 && vue != tab[coor.y + 1][0]))
		return (0);
	return (1);
}

// int	check_vue_column_rev(unsigned int **tab,
// 		t_coor coor, unsigned int tab_size)
// {
// 	t_coor			index;
// 	unsigned int	vue;
// 	unsigned int	max_size;

// 	index.x = coor.x;
// 	index.y = coor.y;
// 	vue = 1;
// 	max_size = tab[coor.y + 1][coor.x + 1];
// 	while (index.y > 0)
// 	{
// 		--index.y;
// 		if (tab[index.y + 1][index.x + 1] > max_size)
// 		{
// 			max_size = tab[index.y + 1][index.x + 1];
// 			++vue;
// 		}
// 	}
// 	if (vue > tab[tab_size + 1][coor.x + 1]
// 		|| (coor.y == tab_size - 1 && vue != tab[tab_size + 1][coor.x + 1]))
// 		return (0);
// 	return (1);
// }

int	check_vue_column_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	t_coor			index;
	unsigned int	vue;
	unsigned int	max_size;

	if (coor.y != tab_size - 1)
		return (1);
	index.x = coor.x;
	index.y = coor.y;
	vue = 1;
	max_size = tab[coor.y + 1][coor.x + 1];
	while (index.y > 0)
	{
		--index.y;
		if (tab[index.y + 1][index.x + 1] > max_size)
		{
			max_size = tab[index.y + 1][index.x + 1];
			++vue;
		}
	}
	if (vue != tab[tab_size + 1][coor.x + 1])
		return (0);
	return (1);
}

int	check_vue_line_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	t_coor			index;
	unsigned int	vue;
	unsigned int	max_size;

	if (coor.x != tab_size - 1)
		return (1);
	index.x = coor.x;
	index.y = coor.y;
	vue = 1;
	max_size = tab[coor.y + 1][coor.x + 1];
	while (index.x > 0)
	{
		--index.x;
		if (tab[index.y + 1][index.x + 1] > max_size)
		{
			max_size = tab[index.y + 1][index.x + 1];
			++vue;
		}
	}
	if (vue != tab[coor.y + 1][tab_size + 1])
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
