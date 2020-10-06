/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/06 19:24:37 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main()
{
	t_sdl		*sdl;
	t_map		*map;
	t_player	*player;
	t_vlist		*vlist;
	t_llist		*llist;
	t_bsp		*bsp_tree;

	sdl = init_sdl();
	clear_screen(sdl);
	map = init_map(0);
	player = init_player(map);
	vlist = set_vlist(map);
	// llist = set_llist(vlist);

	// t_llist		*crs = llist;
	// while (crs)
	// {
	// 	printf("%f\n", crs->normal * 180 / M_PI);
	// 	crs = crs->next;
	// }
	// exit(0);

	// t_vlist		*crs = vlist;
	// while (crs)
	// {
	// 	printf("%d %d\n", crs->crd[X], crs->crd[Y]);
	// 	crs = crs->next;
	// }
	// exit(0);
	bsp_tree = set_tree(vlist);
	
	
	// t_vlist		*cursor;
	// cursor = vlist;
	// while (cursor)
	// {
	// 	printf ("%d\n", cursor->data);
	// 	cursor = cursor->next;
	// }

	
	draw_map(sdl, bsp_tree, map, player);
	
	// printf("projection: %d %d\n", bsp_tree->proj[X], bsp_tree->proj[Y]);
	// printf("len: %f\n", bsp_tree->len);
	// printf("pivot crd: %f %f\n", bsp_tree->pivot[X], bsp_tree->pivot[Y]);
	// printf("direction deg: %f\n", bsp_tree->direct * 180 / M_PI);
	// printf("normal deg: %f\n", bsp_tree->normal * 180 / M_PI);
	// exit(10);

	while (1)
	{
		if (check_event(sdl->event, player, sdl))
		{
			draw_win(sdl, player);
			printf("%f\n", player->direction);
		}
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

char	check_event(SDL_Event event, t_player *player, t_sdl *sdl)
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
			(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			exit(0);
		if (event.type == SDL_KEYDOWN)
		{
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
				player->crd[X] += sin(player->direction);
				player->crd[Y] += cos(player->direction);
				return (1);
			}
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
			if (event.key.keysym.sym == SDLK_q)
			{
				if (check_collision(sdl, player, 1, 0))
					return (0);
				player->direction += 10 * (M_PI / 180);
				return (1);
			}
			if (event.key.keysym.sym == SDLK_e)
			{
				if (check_collision(sdl, player, 1, 0))
					return (0);
				player->direction -= 10 * (M_PI / 180);
				// if (player->direction < 0)
				// 	player->direction = 2 * M_PI - player->direction;
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
