/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:34:41 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/14 18:14:23 by jthuy            ###   ########.fr       */
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


t_llist		*copy_lnode(t_llist *source)
{
	t_llist		*lnode;

	lnode = (t_llist *)malloc(sizeof(t_llist));

	lnode->crd[0][X] = source->crd[0][X];
	lnode->crd[0][Y] = source->crd[0][Y];
	lnode->crd[1][X] = source->crd[1][X];
	lnode->crd[1][Y] = source->crd[1][Y];
	
	lnode->k[LA] = source->k[LA];
	lnode->k[LB] = source->k[LB];
	lnode->k[LC] = source->k[LC];

	lnode->direct = source->direct;
	lnode->normal = source->normal;
	lnode->next = NULL;
	
	return (lnode);
}



// NEED DEEEEEEEL <------
t_llist		*sort_llist(t_llist *llist)  //segmentation fault time to time
{
	t_llist		*slicer;
	t_llist		*temp;
	t_llist		*cursor;
	t_llist		*sorted;
	t_llist		curs_sort;
	int			len;
	int			*arr;
	int			front;
	int			back;
	int			score_old;
	int			score;
	int			numb;
	int			i;
	int			j;

	sorted = NULL;
	
	cursor = llist;
	len = 0;
	while (cursor)
	{
		len += 1;
		cursor = cursor->next;
	}

	// arr = (int *)malloc(sizeof(len));
	arr = (int *)malloc(sizeof(int) * len);
	
	score_old = 1 << 30;
	slicer = llist;
	j = 0;
	while (j < len)
	{
		temp = slicer->next;
		slicer->next = NULL;
		cursor = temp;
		i = 0;
		front = 0;
		back = 0;
		while (i < len - 1)
		{
			if (slicer->k[LA] * cursor->crd[0][X] + slicer->k[LB] * cursor->crd[0][Y] <= -slicer->k[LC] &&
				slicer->k[LA] * cursor->crd[1][X] + slicer->k[LB] * cursor->crd[1][Y] <= -slicer->k[LC])
				{
					front += 1;
					if (!cursor->next)
						break ;
					cursor = cursor->next;
					i += 1;
					continue ;
				}
			if (slicer->k[LA] * cursor->crd[0][X] + slicer->k[LB] * cursor->crd[0][Y] >= -slicer->k[LC] &&
				slicer->k[LA] * cursor->crd[1][X] + slicer->k[LB] * cursor->crd[1][Y] >= -slicer->k[LC])
				{
					back += 1;
					if (!cursor->next)
						break ;
					cursor = cursor->next;
					i += 1;
					continue ;
				}
			front += 1;
			back += 1;
			if (!cursor->next)
				break ;
			cursor = cursor->next;
			i += 1;
		}
		// score = abs(front - back);
		// if (score < score_old)
		// {
		// 	numb = j;
		// 	score_old = score;
		// }
		arr[j] = abs(front - back);
		cursor->next = slicer;
		slicer = temp;
		j += 1;
	}

	// // bubble sort
	int	tmp;
	j = len - 1;
	while (j)
	{
		i = 0;
		cursor = llist;
		while (i < j)
		{
			if (arr[i] > arr[i + 1])
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;

				if (!i)
				{
					temp = llist->next;
					llist->next = llist->next->next;
					temp->next = llist;
					llist = temp;
					cursor = llist;
				}

				else
				{
					temp = cursor->next->next;
					cursor->next->next = temp->next;
					temp->next = cursor->next;
					cursor->next = temp;
				}
				
			}
			if (i)
				cursor = cursor->next;
			i += 1;
		}
		j -= 1;
	}
	
	// j = 0;
	// while (j < len)
	// {
	// 	printf("%d ", arr[j]);
	// 	j += 1;
	// }
	// printf("\n");
	
	// cursor = llist;
	// while (cursor)
	// {
	// 	printf("%d %d\n", cursor->crd[0][X], cursor->crd[0][Y]);
	// 	printf("%d %d\n", cursor->crd[1][X], cursor->crd[1][Y]);
	// 	printf("\n");
	// 	cursor = cursor->next;
	// }
	

	free(arr);
	return (llist);
}

void	add_overallnodes(t_llist *llist, t_map *map)
{
	t_llist		*cursor;
	t_vlist		vertex[2];

	cursor = llist;
	while (cursor->next)
		cursor = cursor->next;

	vertex[0].crd[X] = 0;
	vertex[0].crd[Y] = 0;
	vertex[1].crd[X] = map->width - 1;
	vertex[1].crd[Y] = 0;
	
	cursor->next = create_lnode(&vertex[0], &vertex[1]);
	cursor = cursor->next;
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
}
