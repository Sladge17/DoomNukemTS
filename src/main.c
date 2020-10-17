/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/17 20:05:08 by jthuy            ###   ########.fr       */
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
	llist = set_llist(vlist);
	fix_llist(&llist, map);
	
	// t_llist *tmp;
	// t_llist *tmp2;
	
	// int		step = 0;
	// int		i = 0;
	// tmp = llist;
	// // while ((!tmp->crd[0][Y] && !tmp->crd[1][Y]) || (tmp->crd[0][Y] == map->height - 1 && tmp->crd[1][Y] == map->height - 1) ||
	// // 	(!tmp->crd[0][X] && !tmp->crd[1][X]) || (tmp->crd[0][X] == map->width - 1 && tmp->crd[1][X] == map->width - 1))
	// while ((!tmp->crd[0][Y] && !tmp->crd[1][Y]) || (tmp->crd[0][X] == map->width - 1 && tmp->crd[1][X] == map->width - 1))
	// {
	// 	tmp = tmp->next;
	// 	step += 1;
	// }

	// if (step)
	// {
	// 	if (step == 1)
	// 	{
	// 		tmp = llist;
	// 		llist = llist->next;
	// 		tmp->next = llist->next;
	// 		llist->next = tmp;
	// 	}
	// 	else
	// 	{
	// 		tmp = llist;
	// 		while (i < step - 1)
	// 		{
	// 			tmp = tmp->next;
	// 			i += 1;
	// 		}
	// 		// printf("%f %f  ", tmp->crd[0][X],  tmp->crd[0][Y]);
	// 		// printf("%f %f\n", tmp->crd[1][X],  tmp->crd[1][Y]);
	// 		// exit(0);

	// 		// tmp2 = tmp->next->next;
	// 		// tmp->next->next = llist->next;
	// 		// tmp->next = llist;
	// 		// list = tmp;
	// 		// llist->next = tmp2;

	// 		tmp2 = llist->next;
	// 		llist->next = tmp->next->next;
	// 		tmp->next->next = tmp2;
	// 		tmp2 = tmp->next;
	// 		tmp->next = llist;
	// 		llist = tmp2;
			
	// 		// tmp->next->next = llist->next;
	// 		// tmp->next = llist;
	// 		// llist->next = NULL;
	// 	}
	// 	// printf("%f %f  ", llist->crd[0][X],  llist->crd[0][Y]);
	// 	// printf("%f %f\n", llist->crd[1][X],  llist->crd[1][Y]);
	// 	// exit(0);
		
	// }
	
	// if (!llist->crd[0][Y] && !llist->crd[1][Y])
	// {
	// 	tmp = llist;
	// 	llist = llist->next;
	// 	tmp->next = llist->next;
	// 	llist->next = tmp;
	// }

	// t_llist *crs = llist;
	// while (crs)
	// {
	// 	printf("%f %f  ", crs->crd[0][X],  crs->crd[0][Y]);
	// 	printf("%f %f\n", crs->crd[1][X],  crs->crd[1][Y]);
	// 	crs = crs->next;
	// }
	// exit(0);

	// if (!llist)
	// {
	// 	printf("ok\n");
	// 	exit(0);
	// }

	
	
	bsp_tree = set_tree(llist, map);

	// print_tree(bsp_tree);
	// exit(0);
	


	

	llist = fill_overallnodes(map);
	// NEED ADD OVERALL LINES INTO EXISTING BSP_TREE
	

	add_overallnodes(bsp_tree, llist);
	

	draw_map(sdl, bsp_tree, map, player);


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
			// if (event.key.keysym.sym == SDLK_q)
			// {
			// 	if (check_collision(sdl, player, 1, 0))
			// 		return (0);
			// 	player->direction += 10 * (M_PI / 180);
			// 	return (1);
			// }
			// if (event.key.keysym.sym == SDLK_e)
			// {
			// 	if (check_collision(sdl, player, 1, 0))
			// 		return (0);
			// 	player->direction -= 10 * (M_PI / 180);
			// 	// if (player->direction < 0)
			// 	// 	player->direction = 2 * M_PI - player->direction;
			// 	return (1);
			// }
		}
		// return (0);
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

void	fix_llist(t_llist **llist, t_map *map)
{
	t_llist *tmp;
	t_llist *tmp2;
	
	int		step = 0;
	int		i = 0;
	tmp = *llist;
	// while ((!tmp->crd[0][Y] && !tmp->crd[1][Y]) || (tmp->crd[0][Y] == map->height - 1 && tmp->crd[1][Y] == map->height - 1) ||
	// 	(!tmp->crd[0][X] && !tmp->crd[1][X]) || (tmp->crd[0][X] == map->width - 1 && tmp->crd[1][X] == map->width - 1))
	while ((!tmp->crd[0][Y] && !tmp->crd[1][Y]) || (tmp->crd[0][X] == map->width - 1 && tmp->crd[1][X] == map->width - 1))
	{
		// // len == 1 bad decision
		// if (!tmp->next)
		// 	return ;
		tmp = tmp->next;
		step += 1;
	}

	if (step)
	{
		if (step == 1)
		{
			tmp = *llist;
			*llist = (*llist)->next;
			tmp->next = (*llist)->next;
			(*llist)->next = tmp;
		}
		else
		{
			tmp = *llist;
			while (i < step - 1)
			{
				tmp = tmp->next;
				i += 1;
			}
			// printf("%f %f  ", tmp->crd[0][X],  tmp->crd[0][Y]);
			// printf("%f %f\n", tmp->crd[1][X],  tmp->crd[1][Y]);
			// exit(0);

			// tmp2 = tmp->next->next;
			// tmp->next->next = llist->next;
			// tmp->next = llist;
			// list = tmp;
			// llist->next = tmp2;

			tmp2 = (*llist)->next;
			(*llist)->next = tmp->next->next;
			tmp->next->next = tmp2;
			tmp2 = tmp->next;
			tmp->next = *llist;
			*llist = tmp2;
			
			// tmp->next->next = llist->next;
			// tmp->next = llist;
			// llist->next = NULL;
		}
		// printf("%f %f  ", llist->crd[0][X],  llist->crd[0][Y]);
		// printf("%f %f\n", llist->crd[1][X],  llist->crd[1][Y]);
		// exit(0);
		
	}
}
