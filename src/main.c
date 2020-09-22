/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/22 13:26:02 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main()
{
	t_sdl	*sdl;

	sdl = init_sdl();
	
	int		i = -1;
	while (++i < WIDTH * HEIGHT)
		PIXEL[i] = 0;

	while (1)
	{
		check_event(sdl->event);
		draw_win(sdl);
		SDL_UpdateWindowSurface(sdl->window);
	}
	return (0);
}

t_sdl	*init_sdl()
{
	t_sdl	*sdl;
	
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);
	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	sdl->window = SDL_CreateWindow("DoomNukemTS", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	sdl->surface = SDL_GetWindowSurface(sdl->window);
	return (sdl);
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

void	draw_win(t_sdl *sdl)
{
	int		i = -1;
	while (++i < WIDTH * HEIGHT)
		PIXEL[i] += 1;
}