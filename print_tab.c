/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:24 by herolle           #+#    #+#             */
/*   Updated: 2026/04/28 12:24:17 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	up_lines(unsigned int n)
{
	unsigned int	i = 0;
	(void)write(1, "\r", 1);
	while (i++ < n)
		(void)write(1, "\033[A", 3);
}

void	ft_putchar(char c)
{
	(void)write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	unsigned int	n;

	if (nb < 0)
	{
		(void)write(1, "-", 1);
		n = nb * -1;
	}
	else
		n = nb;
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void	print_tab_vu(unsigned int **tab, unsigned int tab_size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	tab_size += 2;
	while (i < tab_size)
	{
		j = 0;
		while (j < tab_size)
		{
			if ((j == 0 && i == 0) || (j == 0 && i == tab_size - 1)
				|| (j == tab_size - 1 && i == 0)
				|| (j == tab_size - 1 && i == tab_size - 1))
				(void)write(1, " ", 1);
			else
				ft_putnbr(tab[i][j]);
			if (!(tab[i][j] / 10) && j != tab_size - 1)
				(void)write(1, " ", 1);
			++j;
		}
		(void)write(1, "\n", 1);
		++i;
	}
}

void	print_tab(unsigned int **tab, unsigned int tab_size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < tab_size)
	{
		j = 0;
		while (j < tab_size)
		{
			ft_putnbr(tab[i + 1][j + 1]);
			if (!(tab[i + 1][j + 1] / 10) && j != tab_size - 1)
				(void)write(1, " ", 1);
			++j;
		}
		(void)write(1, "\n", 1);
		++i;
	}
}
