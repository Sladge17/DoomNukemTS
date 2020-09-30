/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/30 17:29:20 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bsp	*set_tree(t_vlist *head)
{
	t_bsp		*root;
	t_vlist		*cursor;
	// t_slicer	slicer;
	t_bsp		*slicer;

	root = NULL;
	cursor = head;

	while (1)
	{
		while (cursor->next && cursor->next->data)
		{
			if (!root)
			{
				root = create_node(cursor, cursor->next);
				// slicer.mult[X] = cursor->crd[Y] - cursor->next->crd[Y];
				// slicer.mult[Y] = cursor->next->crd[X] - cursor->crd[X];
				// slicer.addition = (cursor->next->crd[X] * cursor->crd[Y]) - (cursor->crd[X] * cursor->next->crd[Y]);
				cursor = cursor->next;
				continue ;
				// return (root);
			}
			add_node(cursor, cursor->next, root);
			cursor = cursor->next;
		}
		add_node(cursor, head, root);
		if (!cursor->next)
			return (root);
		head = cursor->next->next;
		cursor = head;
		
	}
	
	return (root);
}

t_bsp	*create_node(t_vlist *vertex_0, t_vlist *vertex_1)
{
	t_bsp	*node;

	node = (t_bsp *)malloc(sizeof(t_bsp));
	node->proj[X] = vertex_1->crd[X] - vertex_0->crd[X];
	node->proj[Y] = vertex_1->crd[Y] - vertex_0->crd[Y];
	node->len = sqrt(node->proj[X] * node->proj[X] + node->proj[Y] * node->proj[Y]);
	node->pivot[X] = vertex_0->crd[X] + node->proj[X] / (double)2;
	node->pivot[Y] = vertex_0->crd[Y] + node->proj[Y] / (double)2;
	node->direct = atan2((double)node->proj[Y], (double)node->proj[X]);
	node->normal = node->direct - M_PI_2;
	
	node->mult[X] = vertex_0->crd[Y] - vertex_1->crd[Y];
	node->mult[Y] = vertex_1->crd[X] - vertex_0->crd[X];
	node->addition = (vertex_1->crd[X] * vertex_0->crd[Y]) - (vertex_0->crd[X] * vertex_1->crd[Y]);

	node->front = NULL;
	node->back = NULL;
	return (node);
}


void	add_node(t_vlist *vertex_0, t_vlist *vertex_1, t_bsp *slicer)
{
	t_bsp	*node;

	// node = create_node(vertex_0, vertex_1);
	if (slicer->mult[X] * vertex_1->crd[X] + slicer->mult[Y] * vertex_1->crd[Y] < slicer->addition)
	{
		if (slicer->front)
			add_node(vertex_0, vertex_1, slicer->front);
		else
		{
			node = create_node(vertex_0, vertex_1);
			slicer->front = node;
			printf("Add to front\n");
		}
		
	}
	else
	{
		if (slicer->back)
			add_node(vertex_0, vertex_1, slicer->back);
		else
		{
			node = create_node(vertex_0, vertex_1);
			slicer->back = node;
		printf("Add to back\n");
		}
	}
	// printf("test\n");
}


// void	add_node(t_bsp *root, int index, t_map *map)
// {
// 	while (1)
// 	{
// 		if ((int)map->field[index] - 0x30 < root->index)
// 		{
// 			if (!(root->back))
// 			{
// 				root->back = create_node(index, map);
// 				return ;
// 			}
// 			root = root->back;
// 		}
// 		else
// 		{
// 			if (!(root->front))
// 			{
// 				root->front = create_node(index, map);
// 				return ;
// 			}
// 			root = root->front;
// 		}
// 	}
// }