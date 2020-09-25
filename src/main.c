/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/25 14:02:08 by jthuy            ###   ########.fr       */
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
		check_event(sdl->event, player);
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
	
	cursor[Y] = player->crd[Y] - 1;
	limit[Y] = 0;
	while (limit[Y] < 9)
	{
		cursor[X] = player->crd[X] - 1;
		limit[X] = 0;
		while (limit[X] < 9)
		{
			PIXEL[cursor[X] + WIDTH * cursor[Y]] = 0xFFFF00;
			cursor[X] += 1;
			limit[X] += 1;
		}
		cursor[Y] += 1;
		limit[Y] += 1;
	}
}

void	clear_player(t_sdl *sdl, t_player *player)
{
	// int		cursor[2];
	// int		limit[2];
	
	// cursor[Y] = player->crd[Y] - 1;
	// limit[Y] = 0;
	// while (limit[Y] < 9)
	// {
	// 	cursor[X] = player->crd[X] - 1;
	// 	limit[X] = 0;
	// 	while (limit[X] < 9)
	// 	{
	// 		PIXEL[cursor[X] + WIDTH * cursor[Y]] = 0;
	// 		cursor[X] += 1;
	// 		limit[X] += 1;
	// 	}
	// 	cursor[Y] += 1;
	// 	limit[Y] += 1;
	// }
	int		i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (PIXEL[i] == 0xFFFF00)
			PIXEL[i] = 0;
		i += 1;
	}
	
}



void	check_event(SDL_Event event, t_player *player)
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
				player->crd[X] -= 1;
				return ;
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				player->crd[X] += 1;
				return ;
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				player->crd[Y] -= 1;
				return ;
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				player->crd[Y] += 1;
				return ;
			}
		}
	}
}

void	draw_win(t_sdl *sdl, t_player *player)
{
	clear_player(sdl, player);
	draw_player(sdl, player);
}