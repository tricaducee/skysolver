/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:57:10 by ldebarno          #+#    #+#             */
/*   Updated: 2026/05/10 20:09:47 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sky_solver.h"

unsigned int	check_input(char *s)
{
	unsigned int	ret;
	char			*tmp;

	ret = 0;
	tmp = s;
	if (*s == ' ')
		return (ret);
	while (*s)
	{
		while (*s >= '0' && *s <= '9')
			++s;
		if (*s == ' ')
		{
			++s;
			++ret;
		}
		else if (*s)
			return (0);
	}
	if (ret == 1)
		return (ft_atoi(tmp));
	if (ret)
		++ret;
	if (!(ret % 4) && (ret / 4) > 2)
		return (ret / 4);
	return (0);
}

int	check_nbl(unsigned int *tab, unsigned int tab_size)
{
	unsigned int	i;

	i = 1;
	while (i < tab_size - 1)
	{
		if (tab[i] <= 0 || tab[i] > tab_size)
			return (0);
		i++;
	}
	return (1);
}

int	check_nbc(unsigned int **tab, unsigned int tab_size, unsigned int index)
{
	unsigned int	i;

	i = 1;
	while (i < tab_size - 1)
	{
		if (tab[i][index] <= 0 || tab[i][index] > tab_size)
			return (0);
		i++;
	}
	return (1);
}

int	check_tab(unsigned int **tab, unsigned int tab_size)
{
	if (!check_nbc(tab, tab_size, 0))
		return (0);
	if (!check_nbc(tab, tab_size, tab_size - 1))
		return (0);
	if (!check_nbl(tab[0], tab_size))
		return (0);
	if (!check_nbl(tab[tab_size -1], tab_size))
		return (0);
	return (1);
}
