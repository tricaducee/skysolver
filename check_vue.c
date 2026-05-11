/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:27:39 by herolle           #+#    #+#             */
/*   Updated: 2026/05/11 04:37:57 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"
#define MIN 0
#define MAX 1

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

unsigned int	get_max_box(unsigned int *max_box, unsigned int *unavailable_box)
{
	while (*max_box > 1 && ((1U << (*max_box - 1)) & *unavailable_box))
		--*max_box;
	*unavailable_box |= 1U << (*max_box - 1);
	return (*max_box);
}

unsigned int	get_min_box(unsigned int *min_box, unsigned int *unavailable_box, unsigned int tab_size)
{
	while (*min_box < tab_size && ((1U << (*min_box - 1)) & *unavailable_box))
		++*min_box;
	*unavailable_box |= 1U << (*min_box - 1);
	return (*min_box);
}

int	smart_check_vue_line(t_all *all, t_coor coor, unsigned int tab_size)
{
	unsigned int	**tab = all->map;
	unsigned int	**max_tab = all->heatmap;
	unsigned int	vue[2];
	unsigned int	target_vue;
	unsigned int	max_size[2];
	unsigned int	actual_size[2];
	unsigned int	max_box = tab_size;
	unsigned int	min_box = 1;
	unsigned int	unavailable_box[3];
	unsigned int	i;

	target_vue = tab[coor.y][0];
	if (!target_vue)
		return (1);
	i = 1;
	max_size[MIN] = 0;
	max_size[MAX] = 0;
	vue[MIN] = 0;
	vue[MAX] = 0;
	unavailable_box[2] = tab[coor.y][tab_size + 2];
	unavailable_box[MIN] = unavailable_box[2];
	unavailable_box[MAX] = unavailable_box[MIN];
	while (i <= tab_size)
	{
		if (tab[coor.y][i])
			actual_size[MIN] = actual_size[MAX] = tab[coor.y][i];
		else {
			max_box = max_tab[coor.y][i];
			min_box = 1;
			actual_size[MIN] = get_max_box(&max_box, &unavailable_box[MIN]);
			actual_size[MAX] = get_min_box(&min_box, &unavailable_box[MAX], tab_size);
		}
		if (actual_size[MIN] > max_size[MIN])
		{
			max_size[MIN] = actual_size[MIN];
			++vue[MIN];
		}
		if (actual_size[MAX] > max_size[MAX])
		{
			max_size[MAX] = actual_size[MAX];
			++vue[MAX];
		}
		++i;
	}
	if (unavailable_box[2] == all->full_flag)
		return (target_vue == vue[MIN]);
	return (target_vue >= vue[MIN] && target_vue <= vue[MAX]);
}

int	smart_check_vue_column(t_all *all, t_coor coor, unsigned int tab_size)
{
	unsigned int	**tab = all->map;
	unsigned int	**max_tab = all->heatmap;
	unsigned int	vue[2];
	unsigned int	target_vue;
	unsigned int	max_size[2];
	unsigned int	actual_size[2];
	unsigned int	max_box = tab_size;
	unsigned int	min_box = 1;
	unsigned int	unavailable_box[3];
	unsigned int	i;

	target_vue = tab[0][coor.x];
	if (!target_vue)
		return (1);
	i = 1;
	max_size[MIN] = 0;
	max_size[MAX] = 0;
	vue[MIN] = 0;
	vue[MAX] = 0;
	unavailable_box[2] = tab[tab_size + 2][coor.x];
	unavailable_box[MIN] = unavailable_box[2];
	unavailable_box[MAX] = unavailable_box[MIN];
	while (i <= tab_size)
	{
		if (tab[i][coor.x])
			actual_size[MIN] = actual_size[MAX] = tab[i][coor.x];
		else {
			max_box = max_tab[i][coor.x];
			min_box = 1;
			actual_size[MIN] = get_max_box(&max_box, &unavailable_box[MIN]);
			actual_size[MAX] = get_min_box(&min_box, &unavailable_box[MAX], tab_size);
		}
		if (actual_size[MIN] > max_size[MIN])
		{
			max_size[MIN] = actual_size[MIN];
			++vue[MIN];
		}
		if (actual_size[MAX] > max_size[MAX])
		{
			max_size[MAX] = actual_size[MAX];
			++vue[MAX];
		}
		++i;
	}
	if (unavailable_box[2] == all->full_flag)
		return (target_vue == vue[MIN]);
	return (target_vue >= vue[MIN] && target_vue <= vue[MAX]);
}

int	smart_check_vue_line_rev(t_all *all, t_coor coor, unsigned int tab_size)
{
	unsigned int	**tab = all->map;
	unsigned int	**max_tab = all->heatmap;
	unsigned int	vue[2];
	unsigned int	target_vue;
	unsigned int	max_size[2];
	unsigned int	actual_size[2];
	unsigned int	max_box = tab_size;
	unsigned int	min_box = 1;
	unsigned int	unavailable_box[3];
	unsigned int	i;

	target_vue = tab[coor.y][tab_size + 1];
	if (!target_vue)
		return (1);
	i = tab_size;
	max_size[MIN] = 0;
	max_size[MAX] = 0;
	vue[MIN] = 0;
	vue[MAX] = 0;
	unavailable_box[2] = tab[coor.y][tab_size + 2];
	unavailable_box[MIN] = unavailable_box[2];
	unavailable_box[MAX] = unavailable_box[MIN];
	while (i >= 1)
	{
		if (tab[coor.y][i])
			actual_size[MIN] = actual_size[MAX] = tab[coor.y][i];
		else {
			max_box = max_tab[coor.y][i];
			min_box = 1;
			actual_size[MIN] = get_max_box(&max_box, &unavailable_box[MIN]);
			actual_size[MAX] = get_min_box(&min_box, &unavailable_box[MAX], tab_size);
		}
		if (actual_size[MIN] > max_size[MIN])
		{
			max_size[MIN] = actual_size[MIN];
			++vue[MIN];
		}
		if (actual_size[MAX] > max_size[MAX])
		{
			max_size[MAX] = actual_size[MAX];
			++vue[MAX];
		}
		--i;
	}
	if (unavailable_box[2] == all->full_flag)
		return (target_vue == vue[MIN]);
	return (target_vue >= vue[MIN] && target_vue <= vue[MAX]);
}

int	smart_check_vue_column_rev(t_all *all, t_coor coor, unsigned int tab_size)
{
	unsigned int	**tab = all->map;
	unsigned int	**max_tab = all->heatmap;
	unsigned int	vue[2];
	unsigned int	target_vue;
	unsigned int	max_size[2];
	unsigned int	actual_size[2];
	unsigned int	max_box = tab_size;
	unsigned int	min_box = 1;
	unsigned int	unavailable_box[3];
	unsigned int	i;

	unavailable_box[2] = tab[tab_size + 2][coor.x];
	unavailable_box[MIN] = unavailable_box[2];
	unavailable_box[MAX] = unavailable_box[MIN];
	target_vue = tab[tab_size + 1][coor.x];
	if (!target_vue)
		return (1);
	i = tab_size;
	max_size[MIN] = 0;
	max_size[MAX] = 0;
	vue[MIN] = 0;
	vue[MAX] = 0;
	while (i >= 1)
	{
		if (tab[i][coor.x])
			actual_size[MIN] = actual_size[MAX] = tab[i][coor.x];
		else {
			max_box = max_tab[i][coor.x];
			min_box = 1;
			actual_size[MIN] = get_max_box(&max_box, &unavailable_box[MIN]);
			actual_size[MAX] = get_min_box(&min_box, &unavailable_box[MAX], tab_size);
		}
		if (actual_size[MIN] > max_size[MIN])
		{
			max_size[MIN] = actual_size[MIN];
			++vue[MIN];
		}
		if (actual_size[MAX] > max_size[MAX])
		{
			max_size[MAX] = actual_size[MAX];
			++vue[MAX];
		}
		--i;
	}
	if (unavailable_box[2] == all->full_flag)
		return (target_vue == vue[MIN]);
	return (target_vue >= vue[MIN] && target_vue <= vue[MAX]);
}

int	check_vue_line(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	unsigned int	i;

	target_vue = tab[coor.y][0];
	if (!target_vue)
		return (1);
	i = 1;
	max_size = tab[coor.y][i];
	vue = 1;
	while (i < coor.x && max_size != tab_size)
	{
		if (tab[coor.y][++i] > max_size)
		{
			max_size = tab[coor.y][i];
			if (++vue > target_vue)
				return (0);
		}
	}
	if (coor.x == tab_size)
		return (vue == target_vue);
	return (1);
}

int	check_vue_column(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	unsigned int	i;

	target_vue = tab[0][coor.x];
	if (!target_vue)
		return (1);
	i = 1;
	max_size = tab[i][coor.x];
	vue = 1;
	while (i < coor.y && max_size != tab_size)
	{
		if (tab[++i][coor.x] > max_size)
		{
			max_size = tab[i][coor.x];
			if (++vue > target_vue)
				return (0);
		}
	}
	if (coor.y == tab_size)
		return (vue == target_vue);
	return (1);
}

int	check_vue_line_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	int	i;

	target_vue = tab[coor.y][tab_size + 1];
	if (!target_vue)
		return (1);
	i = coor.x;
	max_size = tab[coor.y][coor.x];
	vue = 1;
	while (i - 1 > 0 && max_size != tab_size)
	{
		if (tab[coor.y][--i] > max_size)
		{
			max_size = tab[coor.y][i];
			if (++vue > target_vue)
				return (0);
		}
	}
	return (vue == target_vue);
}

int	check_vue_column_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	int	i;

	target_vue = tab[tab_size + 1][coor.x];
	if (!target_vue)
		return (1);
	i = coor.y;
	max_size = tab[coor.y][coor.x];
	vue = 1;
	while (i - 1 > 0 && max_size != tab_size)
	{
		if (tab[--i][coor.x] > max_size)
		{
			max_size = tab[i][coor.x];
			if (++vue > target_vue)
				return (0);
		}
	}
	return (vue == target_vue);
}

// int	check_vue_line_final(unsigned int **tab, unsigned int line, unsigned int tab_size)
// {
// 	unsigned int	vue;
// 	unsigned int	max_size;
// 	unsigned int	target_vue;
// 	unsigned int	i;

// 	target_vue = tab[line][0];
// 	if (!target_vue)
// 		return (1);
// 	i = 1;
// 	max_size = 0;
// 	vue = 0;
// 	while (i <= tab_size && max_size != tab_size)
// 	{
// 		if (tab[line][i] > max_size)
// 		{
// 			max_size = tab[line][i];
// 			if (++vue > target_vue)
// 				return (0);
// 		}
// 		++i;
// 	}
// 	return (vue == target_vue);
// }

// int	check_vue_column_final(unsigned int **tab, unsigned int column, unsigned int tab_size)
// {
// 	unsigned int	vue;
// 	unsigned int	max_size;
// 	unsigned int	target_vue;
// 	unsigned int	i;

// 	target_vue = tab[0][column];
// 	if (!target_vue)
// 		return (1);
// 	i = 1;
// 	max_size = 0;
// 	vue = 0;
// 	while (i <= tab_size && max_size != tab_size)
// 	{
// 		if (tab[i][column] > max_size)
// 		{
// 			max_size = tab[i][column];
// 			if (++vue > target_vue)
// 				return (0);
// 		}
// 		++i;
// 	}
// 	return (vue == target_vue);
// }

// int	check_vue_line_rev_final(unsigned int **tab, unsigned int line, unsigned int tab_size)
// {
// 	unsigned int	vue;
// 	unsigned int	max_size;
// 	unsigned int	target_vue;
// 	unsigned int	i;

// 	target_vue = tab[line][tab_size + 1];
// 	if (!target_vue)
// 		return (1);
// 	i = tab_size;
// 	max_size = 0;
// 	vue = 0;
// 	while (i > 0 && max_size != tab_size)
// 	{
// 		if (tab[line][i] > max_size)
// 		{
// 			max_size = tab[line][i];
// 			if (++vue > target_vue)
// 				return (0);
// 		}
// 		--i;
// 	}
// 	return (vue == target_vue);
// }

// int	check_vue_column_rev_final(unsigned int **tab, unsigned int column, unsigned int tab_size)
// {
// 	unsigned int	vue;
// 	unsigned int	max_size;
// 	unsigned int	target_vue;
// 	unsigned int	i;

// 	target_vue = tab[tab_size + 1][column];
// 	if (!target_vue)
// 		return (1);
// 	i = tab_size;
// 	max_size = 0;
// 	vue = 0;
// 	while (i >= 0 && max_size != tab_size)
// 	{
// 		if (tab[--i][column] > max_size)
// 		{
// 			max_size = tab[i][column];
// 			if (++vue > target_vue)
// 				return (0);
// 		}
// 	}
// 	return (vue == target_vue);
// }


// int	check_vue_column(unsigned int **tab,
// 	t_coor coor, unsigned int tab_size)
// {
// 	t_coor			index;
// 	unsigned int	vue;
// 	unsigned int	max_size;

// 	index.x = coor.x;
// 	index.y = 0;
// 	vue = 1;
// 	max_size = tab[index.y + 1][coor.x];
// 	while (index.y < coor.y - 1)
// 	{
// 		++index.y;
// 		if (tab[index.y + 1][coor.x] > max_size)
// 		{
// 			max_size = tab[index.y + 1][coor.x];
// 			++vue;
// 		}
// 	}
// 	if (vue > tab[0][coor.x]
// 		|| (coor.y == tab_size && vue != tab[0][coor.x]))
// 		return (0);
// 	return (1);
// }

// int	check_vue_line(unsigned int **tab, t_coor coor, unsigned int tab_size)
// {
// 	t_coor			index;
// 	unsigned int	vue;
// 	unsigned int	max_size;

// 	index.x = 0;
// 	index.y = coor.y;
// 	vue = 1;
// 	max_size = tab[coor.y][index.x + 1];
// 	while (index.x < coor.x - 1)
// 	{
// 		++index.x;
// 		if (tab[coor.y][index.x + 1] > max_size)
// 		{
// 			max_size = tab[coor.y][index.x + 1];
// 			++vue;
// 		}
// 	}
// 	if (vue > tab[coor.y][0]
// 		|| (coor.x == tab_size && vue != tab[coor.y][0]))
// 		return (0);
// 	return (1);
// }

// int	check_vue_column_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
// {
// 	t_coor			index;
// 	unsigned int	vue;
// 	unsigned int	max_size;

// 	if (coor.y != tab_size)
// 		return (1);
// 	index.x = coor.x;
// 	index.y = coor.y;
// 	vue = 1;
// 	max_size = tab[coor.y][coor.x];
// 	while (index.y - 1 > 0)
// 	{
// 		--index.y;
// 		if (tab[index.y][index.x] > max_size)
// 		{
// 			max_size = tab[index.y][index.x];
// 			++vue;
// 		}
// 	}
// 	if (vue != tab[tab_size + 1][coor.x])
// 		return (0);
// 	return (1);
// }

// int	check_vue_line_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
// {
// 	t_coor			index;
// 	unsigned int	vue;
// 	unsigned int	max_size;

// 	if (coor.x != tab_size)
// 		return (1);
// 	index.x = coor.x;
// 	index.y = coor.y;
// 	vue = 1;
// 	max_size = tab[coor.y][coor.x];
// 	while (index.x - 1 > 0)
// 	{
// 		--index.x;
// 		if (tab[index.y][index.x] > max_size)
// 		{
// 			max_size = tab[index.y][index.x];
// 			++vue;
// 		}
// 	}
// 	if (vue != tab[coor.y][tab_size + 1])
// 		return (0);
// 	return (1);
// }

// int	check_vue_line_rev_norm(unsigned int **tab,
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
// 		!= tab[coor.y + 1][tab_size + 1]))
// 		return (0);
// 	return (1);
// }
