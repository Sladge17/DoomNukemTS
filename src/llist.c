/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:34:41 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/20 14:37:55 by jthuy            ###   ########.fr       */
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

void	fix_llist(t_llist **llist, t_map *map)
{
	t_llist	*cursor[2];
	int		start_id;
	int		i;
	
	start_id = set_startid(*llist, map);
	if (start_id)
	{
		cursor[0] = *llist;
		if (start_id == 1)
		{
			*llist = (*llist)->next;
			cursor[0]->next = (*llist)->next;
			(*llist)->next = cursor[0];
			return ;
		}
		i = -1;
		while (++i < start_id - 1)
			cursor[0] = cursor[0]->next;
		cursor[1] = (*llist)->next;
		(*llist)->next = cursor[0]->next->next;
		cursor[0]->next->next = cursor[1];
		cursor[1] = cursor[0]->next;
		cursor[0]->next = *llist;
		*llist = cursor[1];
	}
}

int		set_startid(t_llist *llist, t_map *map)
{
	int		start_id;
	
	start_id = 0;
	// cursor[0] = *llist;
	// while ((!cursor->crd[0][Y] && !cursor->crd[1][Y]) || (cursor->crd[0][Y] == map->height - 1 && cursor->crd[1][Y] == map->height - 1) ||
	// 	(!cursor->crd[0][X] && !cursor->crd[1][X]) || (cursor->crd[0][X] == map->width - 1 && cursor->crd[1][X] == map->width - 1))
	while ((!llist->crd[0][Y] && !llist->crd[1][Y]) ||
		(llist->crd[0][X] == map->width - 1 && llist->crd[1][X] == map->width - 1))
	{
		if (!llist->next)
			return (0);
		llist = llist->next;
		start_id += 1;
	}
	return (start_id);
}

t_llist	*fill_overallnodes(t_map *map)
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

void	free_llist(t_llist *llist)
{
	while (llist->next)
	{
		free(llist);
		llist = llist->next;
	}
	free(llist);
}
