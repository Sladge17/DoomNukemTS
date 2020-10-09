/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:34:41 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/09 16:37:11 by jthuy            ###   ########.fr       */
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
	lnode->next = NULL;
	
	return (lnode);
}
