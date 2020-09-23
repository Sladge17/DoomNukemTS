/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/23 20:02:22 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main()
{
	t_sdl	*sdl;
	t_map	*map;
	t_bsp	*root;

	sdl = init_sdl();
	map = init_map();
	root = NULL;
	
	// Fill backgraund
	int		i = -1;
	while (++i < WIDTH * HEIGHT)
		PIXEL[i] = 0;

	i = 0;
	while (map->field[i] != '\0')
	{
		if (map->field[i] != '.' && map->field[i] != 'P')
		{
			if (!root)
			{
				root = create_node(i, map);
				i += 1;
				continue ;
			}
			add_node(root, i, map);
		}
		i += 1;
	}
	
	// draw_line(sdl, root->crd[0], root->crd[1], root->front->crd[0], root->front->crd[1]);
	draw_line(sdl, &root->crd[0], &root->front->crd[0]);
	draw_line(sdl, &root->front->crd[0], &root->front->front->back->crd[0]);
	draw_line(sdl, &root->front->front->back->crd[0], &root->front->front->crd[0]);
	draw_line(sdl, &root->front->front->crd[0], &root->crd[0]);

	while (1)
	{
		check_event(sdl->event);
		// draw_win(sdl);
		SDL_UpdateWindowSurface(sdl->window);
	}
	return (0);
}

t_bsp	*create_node(int index, t_map *map)
{
	t_bsp	*node;
	int		scale = 30; // <-- ONLY for draw mini_map

	node = (t_bsp *)malloc(sizeof(t_bsp));
	node->index = (int)map->field[index] - 0x30;
	node->crd[X] = index % map->width * scale;
	node->crd[Y] = index / map->width * scale;
	node->front = NULL;
	node->back = NULL;
	return (node);
}

void	add_node(t_bsp *root, int index, t_map *map)
{
	while (1)
	{
		if ((int)map->field[index] - 0x30 < root->index)
		{
			if (!(root->back))
			{
				root->back = create_node(index, map);
				return ;
			}
			root = root->back;
		}
		else
		{
			if (!(root->front))
			{
				root->front = create_node(index, map);
				return ;
			}
			root = root->front;
		}
	}
}


void	check_event(SDL_Event event)
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
			(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		exit(0);
	}
}

// void	draw_win(t_sdl *sdl)
// {
// 	// need body
// }