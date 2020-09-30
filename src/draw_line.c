/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 18:41:19 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/28 17:30:52 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_line(t_sdl *sdl, int *vert_0, int *vert_1)
{
	char	d[2];
	int		len[2];

	d[X] = vert_1[X] < vert_0[X] ? -1 : 1;
	d[Y] = vert_1[Y] < vert_0[Y] ? -1 : 1;
	len[X] = (vert_1[X] - vert_0[X]) * d[X];
	len[Y] = (vert_1[Y] - vert_0[Y]) * d[Y];
	if (len[X] > len[Y])
	{
		draw_xmore(sdl, vert_0, vert_1, d, len);
		return ;
	}
	draw_ymore(sdl, vert_0, vert_1, d, len);
}

void	draw_xmore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len)
{
	int		cursor[2];
	int		overflow;

	cursor[X] = vert_0[X];
	cursor[Y] = vert_0[Y];
	overflow = 0;
	while (cursor[X] != vert_1[X])
	{
		if ((0 <= cursor[X] && cursor[X] < WIDTH)
			&& (0 <= cursor[Y] && cursor[Y] < HEIGHT))
			PIXEL[cursor[X] + WIDTH * cursor[Y]] = SECTCOLOR;
		overflow += len[1] + 1;
		if (overflow >= len[0] + 1)
		{
			cursor[Y] += d[1];
			overflow -= len[0] + 1;
		}
		cursor[X] += d[0];
	}
}

void	draw_ymore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len)
{
	int		cursor[2];
	int		overflow;

	cursor[X] = vert_0[X];
	cursor[Y] = vert_0[Y];
	overflow = 0;
	while (cursor[Y] != vert_1[Y])
	{
		if ((0 <= cursor[X] && cursor[X] < WIDTH)
			&& (0 <= cursor[Y] && cursor[Y] < HEIGHT))
			PIXEL[cursor[X] + WIDTH * cursor[Y]] = SECTCOLOR;
		overflow += len[0] + 1;
		if (overflow >= len[1] + 1)
		{
			cursor[X] += d[0];
			overflow -= len[1] + 1;
		}
		cursor[Y] += d[1];
	}
}
