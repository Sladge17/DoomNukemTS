/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/17 19:03:41 by jthuy            ###   ########.fr       */
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
		sep_lnode(llist, slicer->k);
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



void	sep_lnode(t_llist *llist, int *slicer_k)
{
	double	*sep_vertex;
	t_llist	*linsert;

	sep_vertex = set_sepvertex(llist, slicer_k);
	linsert = create_linsert(llist, sep_vertex);
	llist->crd[1][X] = sep_vertex[X];
	llist->crd[1][Y] = sep_vertex[Y];
	free(sep_vertex);

	linsert->next = llist->next;
	llist->next = linsert;
}

double	*set_sepvertex(t_llist *llist, int *slicer_k)
{
	double	*sep_vertex;

	sep_vertex = (double *)malloc(sizeof(double) * 2);
	sep_vertex[X] = (slicer_k[LC] * llist->k[LB] - llist->k[LC] * slicer_k[LB]) /
				(double)(llist->k[LA] * slicer_k[LB] - slicer_k[LA] * llist->k[LB]);
	sep_vertex[Y] = (slicer_k[LA] * llist->k[LC] - llist->k[LA] * slicer_k[LC]) /
				(double)(llist->k[LA] * slicer_k[LB] - slicer_k[LA] * llist->k[LB]);
	return (sep_vertex);
}


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

void	add_overallnodes(t_bsp *bsp_tree, t_llist *llist)
{
	while (llist)
	{
		if (add_overnode(bsp_tree, llist))
			llist = llist->next;
		// if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] <= -bsp_tree->k[LC] &&
		// 	bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] <= -bsp_tree->k[LC])
		// {
		// 	// go to front
		// 	if (!bsp_tree->front)
		// 	{
		// 		bsp_tree->front = create_bspnode(llist);
		// 		return ;
		// 	}
		// 	else
		// 	{
		// 		add_overallnodes(bsp_tree->front, llist);
		// 	}
		// 	llist = llist->next;
		// 	continue ;
		// }
		// if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] >= -bsp_tree->k[LC] &&
		// 	bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] >= -bsp_tree->k[LC])
		// {
		// 	// go to back
		// 	if (!bsp_tree->back)
		// 	{
		// 		bsp_tree->back = create_bspnode(llist);
		// 		return ;
		// 	}
		// 	else
		// 	{
		// 		add_overallnodes(bsp_tree->back, llist);
		// 	}
		// 	llist = llist->next;
		// 	continue ;

		// }
		// sep_lnode(llist, bsp_tree->k);
	}
	
}

char	add_overnode(t_bsp *bsp_tree, t_llist *llist)
{
	if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] >= -bsp_tree->k[LC] &&
		bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] >= -bsp_tree->k[LC])
	{
		// go to back

		if (
			llist->crd[0][X] == bsp_tree->back->crd[0][X] &&
			llist->crd[0][Y] == bsp_tree->back->crd[0][Y] &&
			llist->crd[1][X] == bsp_tree->back->crd[1][X] &&
			llist->crd[1][Y] == bsp_tree->back->crd[1][Y])
		{
			free(bsp_tree->back);
			bsp_tree->back = bsp_tree->back->back;
			return (1);
		}
		
		if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] == -bsp_tree->k[LC] &&
			bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] == -bsp_tree->k[LC])
		{
			if (!(add_overnode(bsp_tree->back, llist)))
				return (0);
			else
			{
				return (1);
			}
			
		}
		
		if (!bsp_tree->back)
		{
			bsp_tree->back = create_bspnode(llist);
		}
		else
		{
			if(!(add_overnode(bsp_tree->back, llist)))
				return (0);
		}
		return (1);

	}
	
	if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] <= -bsp_tree->k[LC] &&
		bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] <= -bsp_tree->k[LC])
	{
		// go to front
		if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] == -bsp_tree->k[LC] &&
			bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] == -bsp_tree->k[LC])
		{
			if (!(add_overnode(bsp_tree->back, llist)))
				return (0);
		}
		// if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] == -bsp_tree->k[LC] &&
		// 	bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] == -bsp_tree->k[LC])
		// {
		// // 	if (llist->crd[0][X] == bsp_tree->crd[0][X] &&
		// // 		llist->crd[0][Y] == bsp_tree->crd[0][Y] &&
		// // 		llist->crd[1][X] == bsp_tree->crd[1][X] &&
		// // 		llist->crd[1][Y] == bsp_tree->crd[1][Y])
		// // 	{
		// // 		printf("%f %f\n", llist->crd[0][X], llist->crd[0][Y]);
		// // 		printf("%f %f\n", llist->crd[1][X], llist->crd[1][Y]);
		// // 		// bsp_tree = NULL;
		// // 		// free(bsp_tree);
		// // 		printf("ok\n");
		// // 		return (1);
		// // 	}
		// // 	// if (bsp_tree->back)
		// // 	// {
		// // 	// 	printf("ok\n");
		// // 	// 	// exit(0);
		// // 	// }
		// 	bsp_tree = bsp_tree->back;
			
		// 	return (0);
			
		// }

		
		if (!bsp_tree->front)
		{
			bsp_tree->front = create_bspnode(llist);
		}
		else
		{
			if (!(add_overnode(bsp_tree->front, llist)))
				return (0);
		}
		return (1);
	}
	
	sep_lnode(llist, bsp_tree->k);
	return (0);
}

