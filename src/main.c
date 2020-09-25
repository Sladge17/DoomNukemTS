/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/25 09:50:28 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main()
{
	t_sdl		*sdl;
	t_map		*map;
	t_player	*player;
	t_vlist		*head;
	t_bsp		*root;

	sdl = init_sdl();
	clear_screen(sdl);

	
	map = init_map();
	player = init_player(map);
	
	fill_backgraund(sdl, map->width * SCALER);
	head = set_vlist(map);
	// root = set_tree(map);
	draw_contur(sdl, head);

	map = init_map();
	del_vlist(&head);
	head = set_vlist(map);
	// root = set_tree(map);
	draw_contur(sdl, head);
	
	map = init_map();
	del_vlist(&head);
	head = set_vlist(map);
	// root = set_tree(map);
	draw_contur(sdl, head);

	draw_player(sdl, player);

	while (1)
	{
		if (check_event(sdl->event, player, sdl))
			draw_win(sdl, player);
		SDL_UpdateWindowSurface(sdl->window);
	}
	return (0);
}

void	clear_screen(t_sdl *sdl)
{
	int		i = -1;
	while (++i < WIDTH * HEIGHT)
		PIXEL[i] = 0;
}

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

char	check_event(SDL_Event event, t_player *player, t_sdl *sdl)
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
			(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			exit(0);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				if (check_collision(sdl, player, -1, 0))
					return (0);
				player->crd[X] -= 1;
				return (1);
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				if (check_collision(sdl, player, 1, 0))
					return (0);
				player->crd[X] += 1;
				return (1);
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				if (check_collision(sdl, player, 0, -1))
					return (0);
				player->crd[Y] -= 1;
				return (1);
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				if (check_collision(sdl, player, 0, 1))
					return (0);
				player->crd[Y] += 1;
				return (1);
			}
		}
		return (0);
	}
	return (0);
}

char	check_collision(t_sdl *sdl, t_player *player, char step_x, char step_y)
{
	char	cursor;

	cursor = 1;
	if (step_x)
		while (cursor < 5)
		{
			if (PIXEL[player->crd[X] + cursor * step_x + WIDTH * player->crd[Y]] == SECTCOLOR)
				return (1);
			cursor += 1;
		}
	else
	{
		while (cursor < 5)
		{
			if (PIXEL[player->crd[X] + WIDTH * (player->crd[Y] + cursor * step_y)] == SECTCOLOR)
				return (1);
			cursor += 1;
		}
	}
	return (0);
}

void	draw_win(t_sdl *sdl, t_player *player)
{
	clear_player(sdl, player);
	draw_player(sdl, player);
}