/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:32:03 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/19 13:35:12 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

t_llist		*create_linsert(t_llist *llist, double *sep_vertex)
{
	t_llist		*lnode;

	lnode = (t_llist *)malloc(sizeof(t_llist));

	lnode->crd[0][X] = sep_vertex[X];
	lnode->crd[0][Y] = sep_vertex[Y];
	lnode->crd[1][X] = llist->crd[1][X];
	lnode->crd[1][Y] = llist->crd[1][Y];
	
	lnode->k[LA] = llist->k[LA];
	lnode->k[LB] = llist->k[LB];
	lnode->k[LC] = llist->k[LC];

	lnode->direct = llist->direct;
	lnode->normal = llist->normal;
	lnode->next = NULL;
	
	return (lnode);
}
