/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:27:39 by herolle           #+#    #+#             */
/*   Updated: 2026/05/10 23:45:34 by hermesrolle      ###   ########.fr       */
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

void	set_vars(unsigned int a[2], unsigned int b[2], unsigned int c[2], unsigned int d[2])
{
	a[0] = 0;
	a[1] = 0;
	b[0] = 0;
	b[1] = 0;
	c[0] = 0;
	c[1] = 0;
	d[0] = 0;
	d[1] = 0;
}

int	check_col_vue_lower_bound(t_all *all, t_coor coor)
{
	unsigned int	i;
	unsigned int	h[2];
	unsigned int	first_zero[2];
	unsigned int	max[2];
	unsigned int	vue[2];

	i = 0;
	set_vars(h, first_zero, max, vue);
	while (++i <= all->tab_size)
	{
		h[0] = all->map[i][coor.x];
		if (h[0] == 0 && !first_zero[0])
		{
			h[0] = all->heatmap[i][coor.x];
			first_zero[0] = 1;
		}
		if (h[0] > max[0])
		{
			max[0] = h[0];
			vue[0]++;
		}
		h[1] = all->map[all->tab_size + 1 - i][coor.x];
		if (h[1] == 0 && !first_zero[1])
		{
			h[1] = all->heatmap[all->tab_size + 1 - i][coor.x];
			first_zero[1] = 1;
		}
		if (h[1] > max[1])
		{
			max[1] = h[1];
			vue[1]++;
		}
	}
	return ((vue[0] <= all->map[0][coor.x]) && (vue[1] <= all->map[all->tab_size + 1][coor.x]));
}


int	check_col_vue_upper_bound(t_all *all, t_coor coor)
{
	unsigned int	i;
	unsigned int	h[2];
	unsigned int	first_zero[2];
	unsigned int	max[2];
	unsigned int	vue[2];

	i = 0;
	set_vars(h, first_zero, max, vue);
	while (++i <= all->tab_size)
	{
		h[0] = all->map[i][coor.x];
		if (h[0] == 0)
		{
			h[0] = all->heatmap[i][coor.x];
			vue[0]++;
		}
		else if (h[0] >= max[0])
		{
			max[0] = h[0];
			vue[0]++;
		}
		h[1] = all->map[all->tab_size + 1 - i][coor.x];
		if (h[1] == 0)
		{
			h[1] = all->heatmap[all->tab_size + 1 - i][coor.x];
			vue[1]++;
		}
		else if (h[1] >= max[1])
		{
			max[1] = h[1];
			vue[1]++;
		}
	}
	return ((vue[0] >= all->map[0][coor.x]) && (vue[1] >= all->map[all->tab_size + 1][coor.x]));
}

// int	check_col_vue_lower_bound_rev(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = all->tab_size + 1;
// 	set_vars(h, first_zero, max, vue);
// 	while (--i >= 1)
// 	{
// 		h[1] = all->map[i][coor.x];
// 		if (h[1] == 0 && !first_zero[1])
// 		{
// 			h[1] = all->heatmap[i][coor.x];
// 			first_zero[1] = 1;
// 		}
// 		if (h[1] > max[1])
// 		{
// 			max[1] = h[1];
// 			vue[1]++;
// 		}
// 	}
// 	return ((vue[1] <= all->map[all->tab_size + 1][coor.x]));
// }


// int	check_col_vue_upper_bound_rev(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = all->tab_size + 1;
// 	set_vars(h, first_zero, max, vue);
// 	while (--i >= 1)
// 	{
// 		h[1] = all->map[all->tab_size + 1 - i][coor.x];
// 		if (h[1] == 0)
// 		{
// 			h[1] = all->heatmap[all->tab_size + 1 - i][coor.x];
// 			vue[1]++;
// 		}
// 		else if (h[1] >= max[1])
// 		{
// 			max[1] = h[1];
// 			vue[1]++;
// 		}
// 	}
// 	return ((vue[1] >= all->map[all->tab_size + 1][coor.x]));
// }


int	check_line_vue_lower_bound(t_all *all, t_coor coor)
{
	unsigned int	i;
	unsigned int	h[2];
	unsigned int	first_zero[2];
	unsigned int	max[2];
	unsigned int	vue[2];

	i = 0;
	set_vars(h, first_zero, max, vue);
	while (++i <= all->tab_size)
	{
		h[0] = all->map[coor.y][i];
		if (h[0] == 0 && !first_zero[0])
		{
			h[0] = all->heatmap[coor.y][i];
			first_zero[0] = 1;
		}
		if (h[0] > max[0])
		{
			max[0] = h[0];
			vue[0]++;
		}
		h[1] = all->map[coor.y][all->tab_size + 1 - i];
		if (h[1] == 0 && !first_zero[1])
		{
			h[1] = all->heatmap[coor.y][all->tab_size + 1 - i];
			first_zero[1] = 1;
		}
		if (h[1] > max[1])
		{
			max[1] = h[1];
			vue[1]++;
		}
	}
	return ((vue[0] <= all->map[coor.y][0]) && (vue[1] <= all->map[coor.y][all->tab_size + 1]));
}

// int	check_line_vue_lower_bound_rev(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = all->tab_size + 1;
// 	set_vars(h, first_zero, max, vue);
// 	while (--i >= 1)
// 	{
// 		h[1] = all->map[coor.y][i];
// 		if (h[1] == 0 && !first_zero[1])
// 		{
// 			h[1] = all->heatmap[coor.y][i];
// 			first_zero[1] = 1;
// 		}
// 		if (h[1] > max[1])
// 		{
// 			max[1] = h[1];
// 			vue[1]++;
// 		}
// 	}
// 	return ((vue[1] <= all->map[coor.y][all->tab_size + 1]));
// }

int	check_line_vue_upper_bound(t_all *all, t_coor coor)
{
	unsigned int	i;
	unsigned int	h[2];
	unsigned int	first_zero[2];
	unsigned int	max[2];
	unsigned int	vue[2];

	i = 0;
	set_vars(h, first_zero, max, vue);
	while (++i <= all->tab_size)
	{
		h[0] = all->map[coor.y][i];
		if (h[0] == 0)
		{
			h[0] = all->heatmap[coor.y][i];
			vue[0] += h[0] >= max[0];
		}
		else if (h[0] >= max[0])
		{
			max[0] = h[0];
			vue[0]++;
		}
		h[1] = all->map[coor.y][all->tab_size + 1 - i];
		if (h[1] == 0)
		{
			h[1] = all->heatmap[coor.y][all->tab_size + 1 - i];
			vue[1] += (h[1] >= max[1]);
		}
		else if (h[1] >= max[1])
		{
			max[1] = h[1];
			vue[1]++;
		}
	}
	return ((vue[0] >= all->map[coor.y][0]) && (vue[1] >= all->map[coor.y][all->tab_size + 1]));
}


// int	check_line_vue_upper_bound_rev(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = all->tab_size + 1;
// 	set_vars(h, first_zero, max, vue);
// 	while (--i >= 1)
// 	{
// 		h[1] = all->map[coor.y][i];
// 		if (h[1] == 0)
// 		{
// 			h[1] = all->heatmap[coor.y][i];
// 			vue[1]++;
// 		}
// 		else if (h[1] >= max[1])
// 		{
// 			max[1] = h[1];
// 			vue[1]++;
// 		}
// 	}
// 	return ((vue[1] >= all->map[coor.y][all->tab_size + 1]));
// }

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
	max_size = 0;
	vue = 0;
	while (i <= tab_size && max_size != tab_size && tab[coor.y][i])
	{
		if (tab[coor.y][i] > max_size)
		{
			max_size = tab[coor.y][i];
			if (++vue > target_vue)
				return (0);
		}
		++i;
	}
	return (1);
}

int	check_vue_line_final(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	unsigned int	i;

	target_vue = tab[coor.y][0];
	if (!target_vue)
		return (1);
	i = 1;
	max_size = 0;
	vue = 0;
	while (i <= tab_size && max_size != tab_size)
	{
		if (tab[coor.y][i] > max_size)
		{
			max_size = tab[coor.y][i];
			if (++vue > target_vue)
				return (0);
		}
		++i;
	}
	return (vue == target_vue);
}

int	check_vue_line_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	unsigned int	i;

	target_vue = tab[coor.y][tab_size + 1];
	if (!target_vue)
		return (1);
	i = tab_size;
	max_size = 0;
	vue = 0;
	while (i > 0 && max_size != tab_size)
	{
		if (tab[coor.y][i] > max_size)
		{
			max_size = tab[coor.y][i];
			if (++vue > target_vue)
				return (0);
		}
		--i;
	}
	return (vue == target_vue);
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
	max_size = 0;
	vue = 0;
	while (i <= tab_size && max_size != tab_size && tab[i][coor.x])
	{
		if (tab[i][coor.x] > max_size)
		{
			max_size = tab[i][coor.x];
			if (++vue > target_vue)
				return (0);
		}
		++i;
	}
	return (1);
}

int	check_vue_column_final(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	unsigned int	i;

	target_vue = tab[0][coor.x];
	if (!target_vue)
		return (1);
	i = 1;
	max_size = 0;
	vue = 0;
	while (i <= tab_size && max_size != tab_size)
	{
		if (tab[i][coor.x] > max_size)
		{
			max_size = tab[i][coor.x];
			if (++vue > target_vue)
				return (0);
		}
		++i;
	}
	return (vue == target_vue);
}

int	check_vue_column_rev(unsigned int **tab, t_coor coor, unsigned int tab_size)
{
	unsigned int	vue;
	unsigned int	max_size;
	unsigned int	target_vue;
	unsigned int	i;

	target_vue = tab[tab_size + 1][coor.x];
	if (!target_vue)
		return (1);
	i = tab_size;
	max_size = 0;
	vue = 0;
	while (i > 0 && max_size != tab_size)
	{
		if (tab[i][coor.x] > max_size)
		{
			max_size = tab[i][coor.x];
			if (++vue > target_vue)
				return (0);
		}
		--i;
	}
	return (vue == target_vue);
}


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
