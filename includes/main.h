/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/24 20:22:22 by jthuy            ###   ########.fr       */
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
void	draw_contur(t_sdl *sdl, t_vlist *head);
void	check_event(SDL_Event event);
void	draw_win(t_sdl *sdl);

/*
** init.c
*/
t_sdl	*init_sdl();
t_map	*init_map();

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
** draw_line.c
*/
// void	draw_line(t_sdl *sdl, int crd_x0, int crd_y0, int crd_x1, int crd_y1);
void	draw_line(t_sdl *sdl, int *vert_0, int *vert_1);
void	draw_xmore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);
void	draw_ymore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);

#endif
