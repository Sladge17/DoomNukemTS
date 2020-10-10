/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:34:41 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/09 18:49:15 by jthuy            ###   ########.fr       */
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

void		sort_llist(t_llist *llist)
{
	t_llist		*lcursor;
	t_llist		*sort_llist;
	t_llist		*tmp;
	int			front;
	int			back;
	int			score;

	sort_llist = llist;
	tmp = llist;

	// lcursor = llist->next;
	// while (lcursor)
	// {
	// 	if (llist->k[LA] * lcursor->crd[0][X] + llist->k[LB] * lcursor->crd[0][Y] <= -llist->k[LC] &&
	// 		llist->k[LA] * lcursor->crd[1][X] + llist->k[LB] * lcursor->crd[1][Y] <= -llist->k[LC])
	// 		{
	// 			front += 1;
	// 			lcursor = lcursor->next;
	// 			continue ;
	// 		}
	// 	if (llist->k[LA] * lcursor->crd[0][X] + llist->k[LB] * lcursor->crd[0][Y] >= -llist->k[LC] &&
	// 		llist->k[LA] * lcursor->crd[1][X] + llist->k[LB] * lcursor->crd[1][Y] >= -llist->k[LC])
	// 		{
	// 			back += 1;
	// 			lcursor = lcursor->next;
	// 			continue ;
	// 		}
	// 	lcursor = lcursor->next;
	// }

	while (tmp)
	{
		front = 0;
		back = 0;
		if (llist->k[LA] * tmp->crd[0][X] + llist->k[LB] * tmp->crd[0][Y] <= -llist->k[LC] &&
			llist->k[LA] * tmp->crd[1][X] + llist->k[LB] * tmp->crd[1][Y] <= -llist->k[LC])
			{
				front += 1;
				tmp = tmp->next;
				continue ;
			}
		if (llist->k[LA] * tmp->crd[0][X] + llist->k[LB] * tmp->crd[0][Y] >= -llist->k[LC] &&
			llist->k[LA] * tmp->crd[1][X] + llist->k[LB] * tmp->crd[1][Y] >= -llist->k[LC])
			{
				back += 1;
				tmp = tmp->next;
				continue ;
			}
		tmp = tmp->next;
		
	}
	
	score = abs(front - back);
	printf("%d %d\n", front, back);
	printf("%d\n", score);
	exit(0);
}
