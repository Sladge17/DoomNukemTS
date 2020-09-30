/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/30 19:58:59 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>  //   <----- NEED DELL!!!!!!
# include <stdlib.h>
# include <math.h>

# include "const.h"
# include "struct.h"

/*
** main.c
*/
void	clear_screen(t_sdl *sdl);
char	check_event(SDL_Event event, t_player *player, t_sdl *sdl);
char	check_collision(t_sdl *sdl, t_player *player, char step_x, char step_y);
void	draw_win(t_sdl *sdl, t_player *player);
// void	draw_normal(t_sdl *sdl, t_bsp *root);
void	draw_normal(t_sdl *sdl, t_bsp *root, t_map *map);

/*
** init.c
*/
t_sdl		*init_sdl();
// t_map		*init_map();
t_map	*init_map(int n);
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
** bsp_tree.c
*/
// t_bsp	*set_tree(t_map *map);
t_bsp	*set_tree(t_vlist *head);
// t_bsp	*create_node(int index, t_map *map);
// t_bsp	*create_node(t_vlist *cursor);
t_bsp	*create_node(t_vlist *vertex_0, t_vlist *vertex_1);
// void	add_node(t_bsp *root, int index, t_map *map);
// void	add_node(t_vlist *cursor, t_slicer *slicer);
// void	add_node(t_vlist *vertex_0, t_vlist *vertex_1);
void	add_node(t_vlist *vertex_0, t_vlist *vertex_1, t_bsp *slicer);

/*
** draw_map.c
*/
void	fill_backgraund(t_sdl *sdl, int mapwidth);
// void	draw_contur(t_sdl *sdl, t_vlist *head);
void	draw_contur(t_sdl *sdl, t_vlist *head, t_map *map);
void	draw_player(t_sdl *sdl, t_player *player);
void	clear_player(t_sdl *sdl, t_player *player);

/*
** draw_line.c
*/
void	draw_line(t_sdl *sdl, int *vert_0, int *vert_1);
void	draw_xmore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);
void	draw_ymore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);

#endif
