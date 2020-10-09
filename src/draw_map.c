/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 09:56:11 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/09 16:56:42 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_map(t_sdl *sdl, t_bsp *root, t_map *map, t_player	*player)
{
	fill_backgraund(sdl, map->width * SCALER); // <--- USED SCALAR
	draw_sectors(sdl, root, map);
	draw_player(sdl, player);
}

void	fill_backgraund(t_sdl *sdl, int mapwidth)
{
	int		cursor;
	
	cursor = 0;
	while (cursor < mapwidth * mapwidth)
	{
		PIXEL[cursor % mapwidth + WIDTH * (cursor / mapwidth)] = BACKCOLOR;
		cursor += 1;
	}
}

void	draw_sectors(t_sdl *sdl, t_bsp *root, t_map *map)
{
	draw_wall(sdl, root, map);
	draw_normal(sdl, root, map);
	if (root->front)
		draw_sectors(sdl, root->front, map);
	if (root->back)
		draw_sectors(sdl, root->back, map);
}

void	draw_wall(t_sdl *sdl, t_bsp *root, t_map *map)
{
	map->scale_vert[0][X] = root->crd[0][X] * SCALER;
	map->scale_vert[0][Y] = root->crd[0][Y] * SCALER;
	map->scale_vert[1][X] = root->crd[1][X] * SCALER;
	map->scale_vert[1][Y] = root->crd[1][Y] * SCALER;
	draw_line(sdl, map->scale_vert[0], map->scale_vert[1]);
}

void	draw_normal(t_sdl *sdl, t_bsp *root, t_map *map)
{
	map->scale_vert[0][X] = root->pivot[X] * SCALER;
	map->scale_vert[0][Y] = root->pivot[Y] * SCALER;
	map->scale_vert[1][X] = 10 * cos(-root->normal) + root->pivot[X] * SCALER;
	map->scale_vert[1][Y] = 10 * sin(-root->normal) + root->pivot[Y] * SCALER;
	draw_line(sdl, map->scale_vert[0], map->scale_vert[1]);
}

void	draw_player(t_sdl *sdl, t_player *player)
{
	int		cursor[2];
	int		limit[2];

	player->pastcrd[X] = player->crd[X] - 1;
	player->pastcrd[Y] = player->crd[Y] - 1;
	
	cursor[Y] = player->crd[Y] - 1;
	limit[Y] = 0;
	while (limit[Y] < 3)
	{
		cursor[X] = player->crd[X] - 1;
		limit[X] = 0;
		while (limit[X] < 3)
		{
			PIXEL[cursor[X] + limit[X] + WIDTH * (cursor[Y] + limit[Y])] = PLAYCOLOR;
			limit[X] += 1;
		}
		limit[Y] += 1;
	}
}

void	clear_player(t_sdl *sdl, t_player *player)
{
	int		limit[2];
	
	limit[Y] = 0;
	while (limit[Y] < 3)
	{
		limit[X] = 0;
		while (limit[X] < 3)
		{
			PIXEL[player->pastcrd[X] + limit[X] + WIDTH * (player->pastcrd[Y] + limit[Y])] = BACKCOLOR;
			limit[X] += 1;
		}
		limit[Y] += 1;
	}
	
}