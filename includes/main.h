/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/21 19:12:11 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	int			*pixel;
	SDL_Event	event;
}				t_sdl;

/*
** main.c
*/
t_sdl	*init_sdl();
void	check_event(SDL_Event event);

#endif