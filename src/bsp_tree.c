/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/20 13:41:19 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bsp	*set_tree(t_llist *llist, t_map *map)
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
	bsp_tree = create_bspnode(slicer);
	sep_llist(llist, slicer, &part_llist[0]);
	free(slicer);
	if (part_llist[FRONT])
	{
		if (part_llist[FRONT]->next)
			fix_llist(&(part_llist[FRONT]), map);
		bsp_tree->front = set_tree(part_llist[FRONT], map);
	}
	if (part_llist[BACK])
	{
		if (part_llist[BACK]->next)
			fix_llist(&(part_llist[BACK]), map);
		bsp_tree->back = set_tree(part_llist[BACK], map);
	}
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

void	add_overallnodes(t_bsp *bsp_tree, t_llist *llist)
{
	while (llist)
	{
		if (add_overnode(bsp_tree, llist))
			llist = llist->next;
	}
	
}

char	add_overnode(t_bsp *bsp_tree, t_llist *llist)
{
	if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] == -bsp_tree->k[LC] &&
		bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] == -bsp_tree->k[LC])
		return (add_overnode(bsp_tree->back, llist));
	
	if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] >= -bsp_tree->k[LC] &&
		bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] >= -bsp_tree->k[LC])
	{
		// go to back
		if (del_bspnode(bsp_tree, llist))
			return (1);
		if (!bsp_tree->back)
		{
			bsp_tree->back = create_bspnode(llist);
			return (1);
		}
		return (add_overnode(bsp_tree->back, llist));
	}
	if (bsp_tree->k[LA] * llist->crd[0][X] + bsp_tree->k[LB] * llist->crd[0][Y] <= -bsp_tree->k[LC] &&
		bsp_tree->k[LA] * llist->crd[1][X] + bsp_tree->k[LB] * llist->crd[1][Y] <= -bsp_tree->k[LC])
	{
		// go to front
		if (!bsp_tree->front)
		{
			bsp_tree->front = create_bspnode(llist);
			return (1);
		}
		return (add_overnode(bsp_tree->front, llist));
	}
	sep_lnode(llist, bsp_tree->k);
	return (0);
}

char	del_bspnode(t_bsp *bsp_tree, t_llist *llist)
{
	if (llist->crd[0][X] == bsp_tree->back->crd[0][X] &&
		llist->crd[0][Y] == bsp_tree->back->crd[0][Y] &&
		llist->crd[1][X] == bsp_tree->back->crd[1][X] &&
		llist->crd[1][Y] == bsp_tree->back->crd[1][Y])
	{
		free(bsp_tree->back);
		bsp_tree->back = bsp_tree->back->back;
		return (1);
	}
	return (0);
}
