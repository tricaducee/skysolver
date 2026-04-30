/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_solver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:43 by herolle           #+#    #+#             */
/*   Updated: 2026/04/28 08:42:47 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKY_SOLVER_H
# define SKY_SOLVER_H
# include <stdio.h>

typedef struct S_coor
{
	unsigned int	x;
	unsigned int	y;
}				t_coor;

//---------------SKY_SOLVER---------------//

int				is_end(t_coor coor, unsigned int tab_size);
t_coor			new_coor(t_coor coor, unsigned int tab_size);
int				check_column_and_line(unsigned int **tab,
					t_coor coor, unsigned int box);
unsigned int	put_box(unsigned int **tab, t_coor coor,
					unsigned int tab_size, unsigned int box);
int				sky_solver(unsigned int	**tab, t_coor coor,
					unsigned int tab_size);

//---------------CHECK_VUE---------------//

int				check_min_index(unsigned int **tab, t_coor coor,
					unsigned int tab_size, unsigned int box);
int				check_vue_column(unsigned int **tab,
					t_coor coor, unsigned int tab_size);
int				check_vue_column_rev(unsigned int **tab,
					t_coor coor, unsigned int tab_size);
int				check_vue_line(unsigned int **tab,
					t_coor coor, unsigned int tab_size);
int				check_vue_line_rev(unsigned int **tab,
					t_coor coor, unsigned int tab_size);

//---------------CHECK_TAB---------------//

unsigned int	check_input(char *s);
int				check_nbl(unsigned int *tab, unsigned int tab_size);
int				check_nbc(unsigned int **tab,
					unsigned int tab_size, unsigned int index);
int				check_tab(unsigned int **tab, unsigned int tab_size);

//----------------GEN_TAB----------------//

int				ft_atoi(char *str);
void			put_input_column(unsigned int **tab,
					unsigned int tab_size, t_coor coor, char **user_input);
void			put_input_line(unsigned int **tab,
					unsigned int tab_size, t_coor coor, char **user_input);
void			put_input(unsigned int **tab,
					unsigned int tab_size, char *user_input);
unsigned int	**gen_tab(unsigned int tab_size, char *user_input);

//---------------PRINT_TAB---------------//

void			up_lines(unsigned int n);
void			ft_putchar(char c);
void			ft_putnbr(int nb);
void			print_tab_vu(unsigned int **tab, unsigned int tab_size);
void			print_tab(unsigned int **tab, unsigned int tab_size);

//-----------------UTILS-----------------//

int				ft_strlen(char *str);
int				ft_putstr_fd(int fd, char *str);
void			free_tab(unsigned int **tab);

#endif
