/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:11:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/01 13:38:36 by jthuy            ###   ########.fr       */
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

typedef struct	s_player
{
	int			index;
	int			crd[2];
	int			pastcrd[2];
}				t_player;

typedef struct	s_map
{
	char		*field;
	int			width;
	int			height;
	int			scale_vert[2][2];
}				t_map;

typedef struct		s_vlist
{
	int				data; // <--- MAYBE NOT NEED
	int				index;
	int				crd[2];
	struct s_vlist	*next;
}					t_vlist;

typedef struct		s_bsp
{
	int				index[2];
	int				crd[2][2];
	int				proj[2];
	double			len;
	double			pivot[2]; // <--- MAYBE INT
	double			direct;
	double			normal;
	int				mult[2];
	int				addition;

	struct s_bsp	*front;
	struct s_bsp	*back;
}					t_bsp;

typedef struct		s_slicer
{
	int				mult[2];
	int				addition;
}					t_slicer;


#endif