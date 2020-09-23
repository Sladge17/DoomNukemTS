/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/23 13:52:55 by jthuy            ###   ########.fr       */
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