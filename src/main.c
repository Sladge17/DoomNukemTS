/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/21 18:24:25 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main()
{
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);
	
	SDL_Window	*window = SDL_CreateWindow("doomnukem", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface	*surface = SDL_GetWindowSurface(window);
	int			*pixel = (int *)surface->pixels;

	SDL_Event	windowEvent;


	int		i = -1;
	while (++i < WIDTH * HEIGHT)
	{
		pixel[i] = 0xFF;
	}

	while (1)
	{
		handling_event(&windowEvent);
		// if (SDL_PollEvent(&windowEvent))
		// {
		// 	if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE))
		// 	exit(0);
		// }
		SDL_UpdateWindowSurface(window);
	}
	return (0);
}

void	handling_event(SDL_Event *windowEvent)
{
	if (SDL_PollEvent(&(*windowEvent)))
	{
		if ((*windowEvent).type == SDL_QUIT || ((*windowEvent).type == SDL_KEYDOWN && (*windowEvent).key.keysym.sym == SDLK_ESCAPE))
		exit(0);
	}
}