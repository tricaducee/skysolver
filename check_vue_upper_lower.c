/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vue_upper_lower.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:27:39 by herolle           #+#    #+#             */
/*   Updated: 2026/05/11 00:36:44 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"

int	check_min_index(unsigned int **tab, t_coor coor, unsigned int box)
{
	return (box <= tab[coor.y][coor.x]);
}

// void	set_vars(unsigned int a[2], unsigned int b[2], unsigned int c[2], unsigned int d[2])
// {
// 	a[0] = 0;
// 	a[1] = 0;
// 	b[0] = 0;
// 	b[1] = 0;
// 	c[0] = 0;
// 	c[1] = 0;
// 	d[0] = 0;
// 	d[1] = 0;
// }

// int	check_col_vue_lower_bound(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = 0;
// 	set_vars(h, first_zero, max, vue);
// 	while (++i <= all->tab_size)
// 	{
// 		h[0] = all->map[i][coor.x];
// 		if (h[0] == 0 && !first_zero[0])
// 		{
// 			h[0] = all->heatmap[i][coor.x];
// 			first_zero[0] = 1;
// 		}
// 		if (h[0] > max[0])
// 		{
// 			max[0] = h[0];
// 			vue[0]++;
// 		}
// 		h[1] = all->map[all->tab_size + 1 - i][coor.x];
// 		if (h[1] == 0 && !first_zero[1])
// 		{
// 			h[1] = all->heatmap[all->tab_size + 1 - i][coor.x];
// 			first_zero[1] = 1;
// 		}
// 		if (h[1] > max[1])
// 		{
// 			max[1] = h[1];
// 			vue[1]++;
// 		}
// 	}
// 	return ((vue[0] <= all->map[0][coor.x]) && (vue[1] <= all->map[all->tab_size + 1][coor.x]));
// }


// int	check_col_vue_upper_bound(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = 0;
// 	set_vars(h, first_zero, max, vue);
// 	while (++i <= all->tab_size)
// 	{
// 		h[0] = all->map[i][coor.x];
// 		if (h[0] == 0)
// 		{
// 			h[0] = all->heatmap[i][coor.x];
// 			vue[0]++;
// 		}
// 		else if (h[0] >= max[0])
// 		{
// 			max[0] = h[0];
// 			vue[0]++;
// 		}
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
// 	return ((vue[0] >= all->map[0][coor.x]) && (vue[1] >= all->map[all->tab_size + 1][coor.x]));
// }

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


// int	check_line_vue_lower_bound(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = 0;
// 	set_vars(h, first_zero, max, vue);
// 	while (++i <= all->tab_size)
// 	{
// 		h[0] = all->map[coor.y][i];
// 		if (h[0] == 0 && !first_zero[0])
// 		{
// 			h[0] = all->heatmap[coor.y][i];
// 			first_zero[0] = 1;
// 		}
// 		if (h[0] > max[0])
// 		{
// 			max[0] = h[0];
// 			vue[0]++;
// 		}
// 		h[1] = all->map[coor.y][all->tab_size + 1 - i];
// 		if (h[1] == 0 && !first_zero[1])
// 		{
// 			h[1] = all->heatmap[coor.y][all->tab_size + 1 - i];
// 			first_zero[1] = 1;
// 		}
// 		if (h[1] > max[1])
// 		{
// 			max[1] = h[1];
// 			vue[1]++;
// 		}
// 	}
// 	return ((vue[0] <= all->map[coor.y][0]) && (vue[1] <= all->map[coor.y][all->tab_size + 1]));
// }

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

// int	check_line_vue_upper_bound(t_all *all, t_coor coor)
// {
// 	unsigned int	i;
// 	unsigned int	h[2];
// 	unsigned int	first_zero[2];
// 	unsigned int	max[2];
// 	unsigned int	vue[2];

// 	i = 0;
// 	set_vars(h, first_zero, max, vue);
// 	while (++i <= all->tab_size)
// 	{
// 		h[0] = all->map[coor.y][i];
// 		if (h[0] == 0)
// 		{
// 			h[0] = all->heatmap[coor.y][i];
// 			vue[0] += h[0] >= max[0];
// 		}
// 		else if (h[0] >= max[0])
// 		{
// 			max[0] = h[0];
// 			vue[0]++;
// 		}
// 		h[1] = all->map[coor.y][all->tab_size + 1 - i];
// 		if (h[1] == 0)
// 		{
// 			h[1] = all->heatmap[coor.y][all->tab_size + 1 - i];
// 			vue[1] += (h[1] >= max[1]);
// 		}
// 		else if (h[1] >= max[1])
// 		{
// 			max[1] = h[1];
// 			vue[1]++;
// 		}
// 	}
// 	return ((vue[0] >= all->map[coor.y][0]) && (vue[1] >= all->map[coor.y][all->tab_size + 1]));
// }


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
