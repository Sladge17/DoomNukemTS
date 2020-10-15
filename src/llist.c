/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:34:41 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/15 17:21:23 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_llist		*set_llist(t_vlist *vlist)
{
	t_vlist		*vcursor;
	t_llist		*llist;
	t_llist		*lcursor;
	
	vcursor = vlist;
	llist = NULL;
	while (vcursor->next)
	{
		if (!llist)
		{
			llist = create_lnode(vcursor, vcursor->next);
			lcursor = llist;
			vcursor = vcursor->next;
			continue ;
		}
		if (!vcursor->next->data)
		{
			lcursor->next = create_lnode(vcursor, vlist);
			lcursor = lcursor->next;
			vlist = vcursor->next->next;
			vcursor = vlist;
			continue ;
		}
		lcursor->next = create_lnode(vcursor, vcursor->next);
		lcursor = lcursor->next;
		vcursor = vcursor->next;
	}
	lcursor->next = create_lnode(vcursor, vlist);
	return (llist);
}

t_llist		*create_lnode(t_vlist *vertex_0, t_vlist *vertex_1)
{
	t_llist		*lnode;

	lnode = (t_llist *)malloc(sizeof(t_llist));

	lnode->crd[0][X] = vertex_0->crd[X];
	lnode->crd[0][Y] = vertex_0->crd[Y];
	lnode->crd[1][X] = vertex_1->crd[X];
	lnode->crd[1][Y] = vertex_1->crd[Y];
	
	lnode->k[LA] = vertex_0->crd[Y] - vertex_1->crd[Y];
	lnode->k[LB] = vertex_1->crd[X] - vertex_0->crd[X];
	lnode->k[LC] = vertex_0->crd[X] * vertex_1->crd[Y] - vertex_1->crd[X] * vertex_0->crd[Y];

	lnode->direct = atan2(lnode->k[LA], lnode->k[LB]);
	lnode->normal = lnode->direct + M_PI_2; // MAYBE -
	if (lnode->normal > 2 * M_PI)
		lnode->normal -= 2 * M_PI;
	lnode->next = NULL;
	
	return (lnode);
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

t_llist	*add_overallnodes(t_map *map)
{
	t_llist		*llist;
	t_llist		*cursor;
	t_vlist		vertex[2];

	vertex[0].crd[X] = 0;
	vertex[0].crd[Y] = 0;
	vertex[1].crd[X] = map->width - 1;
	vertex[1].crd[Y] = 0;
	
	llist = create_lnode(&vertex[0], &vertex[1]);
	
	cursor = llist;
	cursor->normal += M_PI;
	if (cursor->normal > 2 * M_PI)
		cursor->normal -= 2 * M_PI;
	cursor->k[LA] *= -1;
	cursor->k[LB] *= -1;
	cursor->k[LC] *= -1;
	
	vertex[0].crd[X] = map->width - 1;
	vertex[0].crd[Y] = 0;
	vertex[1].crd[X] = map->width - 1;
	vertex[1].crd[Y] = map->height - 1;
	
	cursor->next = create_lnode(&vertex[0], &vertex[1]);
	cursor = cursor->next;
	cursor->normal += M_PI;
	if (cursor->normal > 2 * M_PI)
		cursor->normal -= 2 * M_PI;
	cursor->k[LA] *= -1;
	cursor->k[LB] *= -1;
	cursor->k[LC] *= -1;
	
	vertex[0].crd[X] = map->width - 1;
	vertex[0].crd[Y] = map->height - 1;
	vertex[1].crd[X] = 0;
	vertex[1].crd[Y] = map->height - 1;
	
	cursor->next = create_lnode(&vertex[0], &vertex[1]);
	cursor = cursor->next;
	cursor->normal += M_PI;
	if (cursor->normal > 2 * M_PI)
		cursor->normal -= 2 * M_PI;
	cursor->k[LA] *= -1;
	cursor->k[LB] *= -1;
	cursor->k[LC] *= -1;
	
	vertex[0].crd[X] = 0;
	vertex[0].crd[Y] = map->height - 1;
	vertex[1].crd[X] = 0;
	vertex[1].crd[Y] = 0;
	
	cursor->next = create_lnode(&vertex[0], &vertex[1]);
	cursor = cursor->next;
	cursor->normal += M_PI;
	if (cursor->normal > 2 * M_PI)
		cursor->normal -= 2 * M_PI;
	cursor->k[LA] *= -1;
	cursor->k[LB] *= -1;
	cursor->k[LC] *= -1;

	return (llist);
}
