/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/15 18:43:42 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bsp	*set_tree(t_llist *llist)
{
	t_bsp		*bsp_tree;
	int			llen;
	t_llist		*slicer;
	t_llist		*part_llist[2];

	llen = set_llen(llist);
	if (llen == 1)
	{
		bsp_tree = create_bspnode(llist);
		free(llist);
		return (bsp_tree);
	}
	slicer = set_slicer(&llist, llen);
	sep_llist(llist, slicer, &part_llist[0]);
	bsp_tree = create_bspnode(slicer);
	free(slicer);
	if (part_llist[FRONT])
		bsp_tree->front = set_tree(part_llist[FRONT]);
	if (part_llist[BACK])
		bsp_tree->back = set_tree(part_llist[BACK]);
	return (bsp_tree);
}

int		set_llen(t_llist *llist)
{
	int		llen;

	llen = 0;
	while (llist)
	{
		llen += 1;
		llist = llist->next;
	}
	return (llen);
}

t_bsp	*create_bspnode(t_llist *slicer)
{
	t_bsp	*bsp_node;

	bsp_node = (t_bsp *)malloc(sizeof(t_bsp));
	bsp_node->crd[0][X] = slicer->crd[0][X];
	bsp_node->crd[0][Y] = slicer->crd[0][Y];
	bsp_node->crd[1][X] = slicer->crd[1][X];
	bsp_node->crd[1][Y] = slicer->crd[1][Y];

	bsp_node->proj[X] = bsp_node->crd[1][X] - bsp_node->crd[0][X];
	bsp_node->proj[Y] = bsp_node->crd[1][Y] - bsp_node->crd[0][Y];
	bsp_node->len = sqrt(bsp_node->proj[X] * bsp_node->proj[X] +
		bsp_node->proj[Y] * bsp_node->proj[Y]);
	bsp_node->pivot[X] = bsp_node->crd[0][X] + bsp_node->proj[X] / 2;
	bsp_node->pivot[Y] = bsp_node->crd[0][Y] + bsp_node->proj[Y] / 2;

	bsp_node->direct = slicer->direct;
	bsp_node->normal = slicer->normal;
	
	bsp_node->k[LA] = slicer->k[LA];
	bsp_node->k[LB] = slicer->k[LB];
	bsp_node->k[LC] = slicer->k[LC];

	bsp_node->front = NULL;
	bsp_node->back = NULL;

	return (bsp_node);
}

void	sep_llist(t_llist *llist, t_llist *slicer, t_llist **part_llist)
{
	t_llist	*cursor[2];

	part_llist[FRONT] = NULL;
	part_llist[BACK] = NULL;
	while (llist)
	{
		if (slicer->k[LA] * llist->crd[0][X] + slicer->k[LB] * llist->crd[0][Y] <= -slicer->k[LC] &&
			slicer->k[LA] * llist->crd[1][X] + slicer->k[LB] * llist->crd[1][Y] <= -slicer->k[LC])
		{
			fill_partllist(&llist, part_llist, &cursor[0], FRONT);
			continue ;
		}
		if (slicer->k[LA] * llist->crd[0][X] + slicer->k[LB] * llist->crd[0][Y] >= -slicer->k[LC] &&
			slicer->k[LA] * llist->crd[1][X] + slicer->k[LB] * llist->crd[1][Y] >= -slicer->k[LC])
		{
			fill_partllist(&llist, part_llist, &cursor[0], BACK);
			continue ;
		}
		sep_lnode(llist, slicer);
	}
	if (part_llist[FRONT])
		cursor[FRONT]->next = NULL;
	if (part_llist[BACK])
		cursor[BACK]->next = NULL;
}


void	fill_partllist(t_llist **llist, t_llist **part_llist, t_llist **cursor, int part)
{
	if (!part_llist[part])
	{
		part_llist[part] = *llist;
		cursor[part] = *llist;
		*llist = (*llist)->next;
		return ;
	}
	cursor[part]->next = *llist;
	cursor[part] = cursor[part]->next;
	*llist = (*llist)->next;
	return ;
}



void	sep_lnode(t_llist *llist, t_llist *slicer)
{
	double	*sep_vertex;
	t_llist	*linsert;

	sep_vertex = set_sepvertex(llist, slicer);
	linsert = create_linsert(llist, sep_vertex);
	llist->crd[1][X] = sep_vertex[X];
	llist->crd[1][Y] = sep_vertex[Y];
	free(sep_vertex);

	linsert->next = llist->next;
	llist->next = linsert;
}

double	*set_sepvertex(t_llist *llist, t_llist *slicer)
{
	double	*sep_vertex;

	sep_vertex = (double *)malloc(sizeof(double) * 2);
	sep_vertex[X] = (slicer->k[LC] * llist->k[LB] - llist->k[LC] * slicer->k[LB]) /
				(double)(llist->k[LA] * slicer->k[LB] - slicer->k[LA] * llist->k[LB]);
	sep_vertex[Y] = (slicer->k[LA] * llist->k[LC] - llist->k[LA] * slicer->k[LC]) /
				(double)(llist->k[LA] * slicer->k[LB] - slicer->k[LA] * llist->k[LB]);
	return (sep_vertex);
}


t_llist	*set_slicer(t_llist **llist, int llen)
{
	t_llist	*slicer;
	t_llist	*cursor;
	int		*score;
	int		index;
	t_llist	*temp;
	int		step;
	int		front;
	int		back;
	
	score = set_score(*llist, llen);
	// score = (int *)malloc(sizeof(int) * llen);

	// slicer = *llist;
	// index = 0;
	// while (index < llen)
	// {
	// 	temp = slicer->next;
	// 	slicer->next = NULL;
	// 	cursor = temp;
	// 	step = 0;
	// 	front = 0;
	// 	back = 0;
	// 	while (step < llen - 1)
	// 	{
	// 		if (slicer->k[LA] * cursor->crd[0][X] + slicer->k[LB] * cursor->crd[0][Y] <= -slicer->k[LC] &&
	// 			slicer->k[LA] * cursor->crd[1][X] + slicer->k[LB] * cursor->crd[1][Y] <= -slicer->k[LC])
	// 			{
	// 				front += 1;
	// 				if (!cursor->next)
	// 					break ;
	// 				cursor = cursor->next;
	// 				step += 1;
	// 				continue ;
	// 			}
	// 		if (slicer->k[LA] * cursor->crd[0][X] + slicer->k[LB] * cursor->crd[0][Y] >= -slicer->k[LC] &&
	// 			slicer->k[LA] * cursor->crd[1][X] + slicer->k[LB] * cursor->crd[1][Y] >= -slicer->k[LC])
	// 			{
	// 				back += 1;
	// 				if (!cursor->next)
	// 					break ;
	// 				cursor = cursor->next;
	// 				step += 1;
	// 				continue ;
	// 			}
	// 		front += 1;
	// 		back += 1;
	// 		if (!cursor->next)
	// 			break ;
	// 		cursor = cursor->next;
	// 		step += 1;
	// 	}
	// 	score[index] = abs(front - back);
		
	// 	if (cursor)
	// 		cursor->next = slicer;
			
	// 	slicer = temp;
	// 	index += 1;
	// }

	step = 0;
	index = 1;
	while (index < llen)
	{
		if (score[index] < score[step])
			step = index;
		index += 1;
	}
	free(score);
	if (!step)
	{
		slicer = *llist;
		*llist = (*llist)->next;
	}
	else
	{
		cursor = *llist;
		index = 0;
		while (index < step - 1)
		{
			cursor = cursor->next;
			index += 1;
		}
		slicer = cursor->next;
		cursor->next = cursor->next->next;
	}
	return (slicer);
}

int		*set_score(t_llist *llist, int llen)
{
	int		*score;
	int		index;
	t_llist	*temp;
	t_llist	*cursor;
	int		step;
	int		front;
	int		back;
	
	score = (int *)malloc(sizeof(int) * llen);

	index = 0;
	while (index < llen)
	{
		temp = llist->next;
		llist->next = NULL;
		cursor = temp;
		step = 0;
		front = 0;
		back = 0;
		while (step < llen - 1)
		{
			if (llist->k[LA] * cursor->crd[0][X] + llist->k[LB] * cursor->crd[0][Y] <= -llist->k[LC] &&
				llist->k[LA] * cursor->crd[1][X] + llist->k[LB] * cursor->crd[1][Y] <= -llist->k[LC])
				{
					front += 1;
					if (!cursor->next)
						break ;
					cursor = cursor->next;
					step += 1;
					continue ;
				}
			if (llist->k[LA] * cursor->crd[0][X] + llist->k[LB] * cursor->crd[0][Y] >= -llist->k[LC] &&
				llist->k[LA] * cursor->crd[1][X] + llist->k[LB] * cursor->crd[1][Y] >= -llist->k[LC])
				{
					back += 1;
					if (!cursor->next)
						break ;
					cursor = cursor->next;
					step += 1;
					continue ;
				}
			front += 1;
			back += 1;
			if (!cursor->next)
				break ;
			cursor = cursor->next;
			step += 1;
		}
		score[index] = abs(front - back);
		
		if (cursor)
			cursor->next = llist;
			
		llist = temp;
		index += 1;
	}
	return (score);
}
