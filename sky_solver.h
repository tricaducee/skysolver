/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_solver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:15:43 by herolle           #+#    #+#             */
/*   Updated: 2026/05/10 19:49:06 by hermesrolle      ###   ########.fr       */
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

typedef struct S_all
{
	unsigned int	**map;
	unsigned int	**heatmap;
	t_coor			*path_priority;
	unsigned int	tab_size;
	unsigned int	square_tab_size;
	unsigned int	path_size;
}	t_all;

//---------------SKY_SOLVER---------------//

int				is_end(unsigned int curr_i, unsigned int square_tab_size);
int				check_column_and_line_bit_shift(unsigned int **tab,
					t_coor coor, unsigned int tab_size, unsigned int box);
unsigned int	put_box(t_all *all, t_coor curr, unsigned int box);
int				sky_solver(t_all *all, unsigned int curr_i);

//---------------CHECK_VUE---------------//
int				check_col_vue_lower_bound(t_all *all, t_coor coor);
int				check_col_vue_upper_bound(t_all *all, t_coor coor);
int				check_line_vue_lower_bound(t_all *all, t_coor coor);
int				check_line_vue_upper_bound(t_all *all, t_coor coor);
// int				check_min_index(unsigned int **tab, t_coor coor,
// 					unsigned int tab_size, unsigned int box);
int				check_min_index(unsigned int **tab,
					t_coor coor, unsigned int box);
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
void			print_tab_vu_coor(unsigned int **tab, t_coor coor, unsigned int tab_size);
void			print_tab_vu(unsigned int **tab, unsigned int tab_size);
void			print_tab(unsigned int **tab, unsigned int tab_size);

//-----------------UTILS-----------------//

int				ft_strlen(char *str);
int				ft_putstr_fd(int fd, char *str);
void			free_tab(unsigned int **tab);
void			add_manual_number(unsigned int **tab, t_coor t,
				unsigned int box, unsigned int tab_size);

//---------------SKY_EDITOR---------------//

void			sky_editor(t_all *all);

#endif
