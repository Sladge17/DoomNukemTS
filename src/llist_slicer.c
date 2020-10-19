/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_slicer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:39:42 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/19 13:40:31 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_llist	*set_slicer(t_llist **llist, int llen)
{
	t_llist	*slicer;
	t_llist	*cursor;
	int		*score;
	int		index;
	int		sl_index;

	score = set_score(*llist, llen);
	sl_index = set_slicerindex(score, llen);
	free(score);
	if (!sl_index)
	{
		slicer = *llist;
		*llist = (*llist)->next;
		return (slicer);
	}
	cursor = *llist;
	index = 0;
	while (index < sl_index - 1)
	{
		cursor = cursor->next;
		index += 1;
	}
	slicer = cursor->next;
	cursor->next = cursor->next->next;
	return (slicer);
}

int		*set_score(t_llist *llist, int llen)
{
	int		*score;
	int		index;
	t_llist	*temp;
	t_llist	*cursor;
	int		part[2];
	
	score = (int *)malloc(sizeof(int) * llen);
	index = 0;
	while (index < llen)
	{
		temp = llist->next;
		llist->next = NULL;
		cursor = temp;
		part[FRONT] = 0;
		part[BACK] = 0;
		while (1)
		{
			if (llist->k[LA] * cursor->crd[0][X] + llist->k[LB] * cursor->crd[0][Y] <= -llist->k[LC] &&
				llist->k[LA] * cursor->crd[1][X] + llist->k[LB] * cursor->crd[1][Y] <= -llist->k[LC])
				{
					part[FRONT] += 1;
					if (!cursor->next)
						break ;
					cursor = cursor->next;
					continue ;
				}
			if (llist->k[LA] * cursor->crd[0][X] + llist->k[LB] * cursor->crd[0][Y] >= -llist->k[LC] &&
				llist->k[LA] * cursor->crd[1][X] + llist->k[LB] * cursor->crd[1][Y] >= -llist->k[LC])
				{
					part[BACK] += 1;
					if (!cursor->next)
						break ;
					cursor = cursor->next;
					continue ;
				}
			part[FRONT] += 1;
			part[BACK] += 1;
			if (!cursor->next)
				break ;
			cursor = cursor->next;
		}
		score[index] = abs(part[FRONT] - part[BACK]);
		cursor->next = llist;
		llist = temp;
		index += 1;
	}
	return (score);
}

int		set_slicerindex(int *score, int llen)
{
	int		sl_index;
	int		index;

	sl_index = 0;
	index = 1;
	while (index < llen)
	{
		if (score[index] < score[sl_index])
			sl_index = index;
		index += 1;
	}
	return (sl_index);
}
