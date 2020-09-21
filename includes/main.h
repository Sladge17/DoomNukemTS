/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/21 18:22:40 by jthuy            ###   ########.fr       */
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

/*
** main.c
*/
void	handling_event(SDL_Event *windowEvent);

#endif