/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/24 15:43:51 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main()
{
	t_sdl	*sdl;
	t_map	*map;
	t_vlist	*head;
	t_bsp	*root;

	sdl = init_sdl();
	map = init_map();

	head = set_vlist(map);
	
	// print vlist data
	t_vlist	*vcursor;
	vcursor = head;
	while (1)
	{
		printf("%d\n", vcursor->data);
		if (vcursor->next)
		{
			vcursor = vcursor->next;
			continue ;
		}
		break ;
	}
	// exit(0);
	
	
	
	root = set_tree(map);
	
	// Fill backgraund
	int		i = -1;
	while (++i < WIDTH * HEIGHT)
		PIXEL[i] = 0;


	
	// draw_line(sdl, root->crd[0], root->crd[1], root->front->crd[0], root->front->crd[1]);
	draw_line(sdl, &head->crd[0], &head->next->crd[0]);
	draw_line(sdl, &head->next->crd[0], &head->next->next->next->crd[0]);

	while (1)
	{
		check_event(sdl->event);
		// draw_win(sdl);
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

// void	draw_win(t_sdl *sdl)
// {
// 	// need body
// }