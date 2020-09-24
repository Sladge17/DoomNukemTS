/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/24 13:09:24 by jthuy            ###   ########.fr       */
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

// t_vlist	*set_vlist(t_map *map)
// {
// 	t_vlist	*head;
// 	int		i;

// 	head = NULL;
// 	i = 0;
// 	while (map->field[i] != '\0')
// 	{
// 		if (map->field[i] != '.' && map->field[i] != 'P')
// 		{
// 			if (!head)
// 			{
// 				head = create_vnode(i, map);
// 				i += 1;
// 				continue ;
// 			}
// 			add_vnode(head, i, map);
// 		}
// 		i += 1;
// 	}
// 	return (head);
// }

// t_vlist	*create_vnode(int index, t_map *map)
// {
// 	t_vlist	*node;
// 	int		scale = 30; // <-- ONLY for draw mini_map

// 	node = (t_vlist *)malloc(sizeof(t_vlist));
// 	node->data = (int)map->field[index] - 0x30;
// 	node->index = index;
// 	node->crd[X] = index % map->width * scale;
// 	node->crd[Y] = index / map->width * scale;
// 	node->next = NULL;
// 	return (node);
// }

// void	add_vnode(t_vlist *head, int index, t_map *map)
// {
// 	while (head->next)
// 		head = head->next;
// 	head->next = create_vnode(index, map);
// }





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