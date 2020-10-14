/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:11:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/14 16:44:54 by jthuy            ###   ########.fr       */
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
	double		direction;
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
	int				data;
	int				index;
	int				crd[2];
	struct s_vlist	*next;
}					t_vlist;

typedef struct		s_llist
{
	// int				crd[2][2];
	double			crd[2][2];
	int				k[3];
	double			direct;
	double			normal;
	struct s_llist	*next;
}					t_llist;

typedef struct		s_bsp
{
	double			crd[2][2];
	double			proj[2];
	double			len;
	double			pivot[2];
	double			direct;
	double			normal;
	int				k[3];
	struct s_bsp	*front;
	struct s_bsp	*back;
}					t_bsp;

#endif