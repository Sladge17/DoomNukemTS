/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/25 10:04:07 by jthuy            ###   ########.fr       */
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

/*
** init.c
*/
t_sdl		*init_sdl();
t_map		*init_map();
t_player	*init_player(t_map *map);

/*
** vlist.c
*/
t_vlist	*set_vlist(t_map *map);
t_vlist	*create_vnode(int index, t_map *map);
void	add_vnode(t_vlist **head, int index, t_map *map);
void	del_vlist(t_vlist **head);

/*
** bsp_tree.c
*/
t_bsp	*set_tree(t_map *map);
t_bsp	*create_node(int index, t_map *map);
void	add_node(t_bsp *root, int index, t_map *map);

/*
** draw_map.c
*/
void	fill_backgraund(t_sdl *sdl, int mapwidth);
void	draw_contur(t_sdl *sdl, t_vlist *head);
void	draw_player(t_sdl *sdl, t_player *player);
void	clear_player(t_sdl *sdl, t_player *player);

/*
** draw_line.c
*/
void	draw_line(t_sdl *sdl, int *vert_0, int *vert_1);
void	draw_xmore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);
void	draw_ymore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);

#endif
