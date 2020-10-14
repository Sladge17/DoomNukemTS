/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/14 14:20:24 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>  //   <----- NEED DELL!!!!!!
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

# include "const.h"
# include "struct.h"

/*
** main.c
*/
void	clear_screen(t_sdl *sdl);
char	check_event(SDL_Event event, t_player *player, t_sdl *sdl);
char	check_collision(t_sdl *sdl, t_player *player, char step_x, char step_y);
void	draw_win(t_sdl *sdl, t_player *player);
void	draw_normal(t_sdl *sdl, t_bsp *root, t_map *map);

/*
** init.c
*/
t_sdl		*init_sdl();
t_map		*init_map(int n);
t_player	*init_player(t_map *map);

/*
** vlist.c
*/
t_vlist	*set_vlist(t_map *map);
t_vlist	*set_vtail(t_map *map);
t_vlist	*create_vnode(int index, t_map *map);
t_vlist	*create_vempty();
void	add_vnode(t_vlist **head, int index, t_map *map);
void	del_vlist(t_vlist **head);

/*
** llist.c
*/
t_llist		*set_llist(t_vlist *vlist);
t_llist		*create_lnode(t_vlist *vertex_0, t_vlist *vertex_1);
t_llist		*copy_lnode(t_llist *source);
t_llist		*sort_llist(t_llist *llist);
void		add_overallnodes(t_llist *llist, t_map *map);

/*
** bsp_tree.c
*/

// t_bsp	*set_tree(t_llist *llist);
// t_bsp	*create_bspnode(double *vertex_0, double *vertex_1, t_llist *lcursor);
// void	add_bspnode(t_bsp *bsp_tree, t_llist *lcursor, double *vertex_0, double *vertex_1);
// double	*sep_lnode(t_bsp *bsp_tree, t_llist *lcursor);

t_bsp	*set_tree(t_llist *llist);
t_llist	*set_slicer(t_llist **llist);
t_bsp	*create_bspnode(t_llist *slicer);
// void	add_bspnode(t_bsp *bsp_tree, t_llist *lcursor, double *vertex_0, double *vertex_1);
// double	*sep_lnode(t_bsp *bsp_tree, t_llist *lcursor);
double	*sep_lnode(t_llist *llist, t_llist *slicer);


/*
** draw_map.c
*/
void	draw_map(t_sdl *sdl, t_bsp *root, t_map *map, t_player	*player);
void	fill_backgraund(t_sdl *sdl, int mapwidth);
void	draw_sectors(t_sdl *sdl, t_bsp *root, t_map *map);
void	draw_wall(t_sdl *sdl, t_bsp *root, t_map *map);
void	draw_normal(t_sdl *sdl, t_bsp *root, t_map *map);
void	draw_player(t_sdl *sdl, t_player *player);
void	clear_player(t_sdl *sdl, t_player *player);

/*
** draw_line.c
*/
void	draw_line(t_sdl *sdl, int *vert_0, int *vert_1);
void	draw_xmore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);
void	draw_ymore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);

#endif
