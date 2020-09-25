/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 09:56:11 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/25 09:56:55 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fill_backgraund(t_sdl *sdl, int mapwidth)
{
	int		cursor;
	char	fillflag = 1;

	cursor = 0;
	while (cursor < mapwidth * mapwidth)
	{
		PIXEL[cursor % mapwidth + WIDTH * (cursor / mapwidth)] = BACKCOLOR;
		cursor += 1;
	}
}

void	draw_contur(t_sdl *sdl, t_vlist *head)
{
	t_vlist		*cursor;

	cursor = head;
	while (cursor->next)
	{
		draw_line(sdl, &cursor->crd[0], &cursor->next->crd[0]);
		cursor = cursor->next;
	}
	draw_line(sdl, &cursor->crd[0], &head->crd[0]);
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