/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:10 by herolle           #+#    #+#             */
/*   Updated: 2026/05/10 20:53:43 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"
#include <stdlib.h>

int	ft_atoi(char *str)
{
	unsigned int	ret;

	ret = 0;
	while (*str && (*str >= '0' && *str <= '9'))
		ret = (ret * 10) + (*(str++) - '0');
	return (ret);
}

void	put_input_column(unsigned int **tab,
	unsigned int tab_size, t_coor coor, char **user_input)
{
	tab[coor.y][coor.x - 1] = 0;
	tab[coor.y][tab_size - 1] = 0;
	while (coor.x < tab_size - 1 && **user_input)
	{
		tab[coor.y][coor.x++] = ft_atoi(*user_input);
		while (**user_input >= '0' && **user_input <= '9')
			++*user_input;
		if (**user_input == ' ')
			++*user_input;
	}
}

void	put_input_line(unsigned int **tab,
	unsigned int tab_size, t_coor coor, char **user_input)
{
	tab[coor.y - 1][coor.x] = 0;
	tab[tab_size - 1][coor.x] = 0;
	while (coor.y < tab_size - 1 && **user_input)
	{
		tab[coor.y++][coor.x] = ft_atoi(*user_input);
		while (**user_input >= '0' && **user_input <= '9')
			++*user_input;
		if (**user_input == ' ')
			++*user_input;
	}
}

int		no_input(unsigned int **tab, unsigned int tab_size, char *user_input)
{
	t_coor	coor;

	coor.y = 0;
	while (coor.y < tab_size)
	{
		coor.x = 0;
		while (coor.x < tab_size)
			tab[coor.y][coor.x++] = 0;
		++coor.y;
	}
	while (*user_input && *user_input != ' ')
		++user_input;
	if (*user_input)
		return (0);
	return (1);
}

void	put_input(unsigned int **tab, unsigned int tab_size, char *user_input)
{
	t_coor	coor;

	coor.x = 1;
	coor.y = 0;
	put_input_column(tab, tab_size, coor, &user_input);
	coor.x = 1;
	coor.y = tab_size - 1;
	put_input_column(tab, tab_size, coor, &user_input);
	coor.x = 0;
	coor.y = 1;
	put_input_line(tab, tab_size, coor, &user_input);
	coor.x = tab_size - 1;
	coor.y = 1;
	put_input_line(tab, tab_size, coor, &user_input);
}

unsigned int	**gen_tab(unsigned int tab_size, char *user_input)
{
	unsigned int	**tab;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	tab = malloc((tab_size + 4) * sizeof(int *));
	if (!tab)
		return (NULL);
	while (i < tab_size + 3)
	{
		tab[i] = malloc((tab_size + 3) * sizeof(int));
		if (!tab[i])
		{
			free_tab(tab);
			return (NULL);
		}
		tab[i++][tab_size + 2] = (1 << tab_size);
	}
	j = 0;
	tab[i--] = NULL;
	while (j < tab_size + 3)
		tab[i][j++] = (1 << tab_size);
	if (!no_input(tab, tab_size + 2, user_input))
		put_input(tab, tab_size + 2, user_input);
	return (tab);
}
