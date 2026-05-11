/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:34 by herolle           #+#    #+#             */
/*   Updated: 2026/05/11 03:39:45 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"
#include <unistd.h>

int	is_end(unsigned int curr_i, unsigned int path_size)
{
	if (curr_i == path_size - 1)
		return (1);
	return (0);
}

int	check_column_and_line_bit_shift(unsigned int **tab, t_coor coor, unsigned int tab_size, unsigned int box)
{
	const unsigned int	i = (1 << (box - 1));
	const unsigned int	delta = tab_size + 2;
	int					ret =  1;
	// (void)full_flag;

	if (!(tab[delta][coor.x] & i) && !(tab[coor.y][delta] & i))
	{
		tab[delta][coor.x] |= i;
		tab[coor.y][delta] |= i;
		// if (tab[delta][coor.x] == full_flag)
		// 	ret = check_vue_column_final(tab, coor.x, tab_size) && check_vue_column_rev(tab, coor, tab_size);
		// if (ret && tab[coor.y][delta] == full_flag)
		// 	return (check_vue_line_final(tab, coor.y, tab_size) && check_vue_line_rev(tab, coor, tab_size));
		return (ret);
	}
	return (0);
}

unsigned int	put_box(t_all *all, t_coor coor, unsigned int box)
{
	t_coor			boxes_save;
	unsigned int	**tab;

	tab = all->map;
	boxes_save.x = tab[all->tab_size + 2][coor.x];
	boxes_save.y = tab[coor.y][all->tab_size + 2];
	//printf("trying: (%u, %u)\n", coor.x, coor.y);
	while (1)
	{
		tab[coor.y][coor.x] = box;
		if (check_column_and_line_bit_shift(all->map, coor, all->tab_size, box)
			// && check_line_vue_lower_bound(all, coor)
			// 	//&& check_line_vue_lower_bound_rev(all, coor)
			// && check_line_vue_upper_bound(all, coor)
			// 	//&& check_line_vue_upper_bound_rev(all, coor)
			// && check_col_vue_lower_bound(all, coor)
			// 	//&& check_col_vue_lower_bound_rev(all, coor)
			// && check_col_vue_upper_bound(all, coor)
				//&& check_col_vue_upper_bound_rev(all, coor)
			//&& all->map[][] all->full_flag check_vue_line(tab, coor, all->tab_size)
			&& smart_check_vue_line(all, coor, all->tab_size)
			&& smart_check_vue_column(all, coor, all->tab_size)
			&& smart_check_vue_line_rev(all, coor, all->tab_size)
			&& smart_check_vue_column_rev(all, coor, all->tab_size)
		)
			return (box);
		tab[all->tab_size + 2][coor.x] = boxes_save.x;
		tab[coor.y][all->tab_size + 2] = boxes_save.y;
		--box;
		if (!box)
			break ;
	}
	return (0);
}

int	sky_solver(t_all *all, unsigned int coor_i)
{
	unsigned int	box;
	t_coor			boxes_save;
	int				ret;
	unsigned int	**tab;
	const t_coor	coor = all->path_priority[coor_i];	

	//box = all->tab_size;
	box = all->heatmap[coor.y][coor.x];
	tab = all->map;
	boxes_save.x = tab[all->tab_size + 2][coor.x];
	boxes_save.y = tab[coor.y][all->tab_size + 2];
	while (1)
	{
		box = put_box(all, coor, box);
		if (!box)
		{
			tab[coor.y][coor.x] = 0;
			return (0);
		}
		#ifdef ANIMATE
			up_lines(all->tab_size + 2);
		#endif
		if (is_end(coor_i, all->path_size))
			return (1);
		#ifdef ANIMATE
			print_tab_vu_coor(tab, coor, all->tab_size);
		#endif
		ret = sky_solver(all, coor_i + 1);
		if (ret)
			return (ret);
		tab[all->tab_size + 2][coor.x] = boxes_save.x;
		tab[coor.y][all->tab_size + 2] = boxes_save.y;
		--box;
		if (!box)
		{
			tab[coor.y][coor.x] = 0;
			return (0);
		}
	}
	return (ret);
}
