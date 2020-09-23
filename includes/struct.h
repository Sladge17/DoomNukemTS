/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:11:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/23 13:40:31 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Event		event;
}					t_sdl;

typedef struct	s_map
{
	char		*field;
	int			width;
	int			height;
}				t_map;

typedef struct		s_bsp
{
	int				data;
	struct s_bsp	*left;
	struct s_bsp	*right;
}					t_bsp;

#endif