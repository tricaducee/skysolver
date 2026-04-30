/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:17 by herolle           #+#    #+#             */
/*   Updated: 2026/04/28 12:14:29 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	unsigned int	tab_size;
	unsigned int	**tab;
	t_coor			coor;

	if (ac != 2)
		return (ft_putstr_fd(2, "Error\n"));
	tab_size = check_input(av[1]);
	if (!tab_size)
		return (ft_putstr_fd(2, "Error\n"));
	tab = gen_tab(tab_size, av[1]);
	if (!tab)
		return (ft_putstr_fd(2, "Error\n"));
	if (!check_tab(tab, tab_size + 2))
		return (ft_putstr_fd(2, "Error\n"));
	coor.x = 0;
	coor.y = 0;
	#ifdef ANIMATE
		unsigned int	i = 0;
		while (i++ < tab_size + 2)
			write(1, "\n", 1);
	#endif
	if (!sky_solver(tab, coor, tab_size))
		return (ft_putstr_fd(2, "\033[0;31mError\n"));
	else
		print_tab_vu(tab, tab_size);
	free_tab(tab);
	return (0);
}
