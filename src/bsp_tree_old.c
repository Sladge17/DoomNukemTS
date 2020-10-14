/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/09 16:52:15 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bsp	*set_tree(t_llist *llist)
{
	t_bsp		*bsp_tree;
	double		*vertex[2];
	
	vertex[0] = (double *)malloc(sizeof(double) * 2);
	vertex[1] = (double *)malloc(sizeof(double) * 2);
	bsp_tree = NULL;
	while (llist)
	{
		vertex[0][X] = llist->crd[0][X];
		vertex[0][Y] = llist->crd[0][Y];
		vertex[1][X] = llist->crd[1][X];
		vertex[1][Y] = llist->crd[1][Y];
		if (!bsp_tree)
		{
			bsp_tree = create_bspnode(vertex[0], vertex[1], llist);
			llist = llist->next;
			continue ;
		}
		add_bspnode(bsp_tree, llist, vertex[0], vertex[1]);
		llist = llist->next;
	}
	free(vertex[0]);
	free(vertex[1]);
	return (bsp_tree);
}

t_bsp	*create_bspnode(double *vertex_0, double *vertex_1, t_llist *lcursor)
{
	t_bsp	*bsp_node;

	bsp_node = (t_bsp *)malloc(sizeof(t_bsp));
	bsp_node->crd[0][X] = vertex_0[X];
	bsp_node->crd[0][Y] = vertex_0[Y];
	bsp_node->crd[1][X] = vertex_1[X];
	bsp_node->crd[1][Y] = vertex_1[Y];

	bsp_node->proj[X] = vertex_1[X] - vertex_0[X];
	bsp_node->proj[Y] = vertex_1[Y] - vertex_0[Y];
	bsp_node->len = sqrt(bsp_node->proj[X] * bsp_node->proj[X] + bsp_node->proj[Y] * bsp_node->proj[Y]);
	bsp_node->pivot[X] = vertex_0[X] + bsp_node->proj[X] / 2;
	bsp_node->pivot[Y] = vertex_0[Y] + bsp_node->proj[Y] / 2;

	bsp_node->direct = lcursor->direct;
	bsp_node->normal = lcursor->normal;
	
	bsp_node->k[LA] = lcursor->k[LA];
	bsp_node->k[LB] = lcursor->k[LB];
	bsp_node->k[LC] = lcursor->k[LC];

	bsp_node->front = NULL;
	bsp_node->back = NULL;

	return (bsp_node);
}


void	add_bspnode(t_bsp *bsp_tree, t_llist *lcursor, double *vertex_0, double *vertex_1)
{
	t_bsp	*bsp_node;
	double	*sep_vertex;

	if (bsp_tree->k[LA] * vertex_0[X] + bsp_tree->k[LB] * vertex_0[Y] <= -bsp_tree->k[LC] &&
		bsp_tree->k[LA] * vertex_1[X] + bsp_tree->k[LB] * vertex_1[Y] <= -bsp_tree->k[LC])
	{
		if (bsp_tree->front)
		{
			add_bspnode(bsp_tree->front, lcursor, vertex_0, vertex_1);
			return ;
		}
		bsp_node = create_bspnode(vertex_0, vertex_1, lcursor);
		bsp_tree->front = bsp_node;
		return ;
	}
	if (bsp_tree->k[LA] * vertex_0[X] + bsp_tree->k[LB] * vertex_0[Y] >= -bsp_tree->k[LC] &&
		bsp_tree->k[LA] * vertex_1[X] + bsp_tree->k[LB] * vertex_1[Y] >= -bsp_tree->k[LC])
	{
		if (bsp_tree->back)
		{
			add_bspnode(bsp_tree->back, lcursor,  vertex_0, vertex_1);
			return ;
		}
		bsp_node = create_bspnode(vertex_0, vertex_1, lcursor);
		bsp_tree->back = bsp_node;
		return ;
	}
	sep_vertex = sep_lnode(bsp_tree, lcursor);
	add_bspnode(bsp_tree, lcursor, vertex_0, sep_vertex);
	add_bspnode(bsp_tree, lcursor, sep_vertex, vertex_1);
	free(sep_vertex);
}

double	*sep_lnode(t_bsp *bsp_tree, t_llist *lcursor)
{
	double	*sep_vertex;

	sep_vertex = (double *)malloc(sizeof(double) * 2);
	sep_vertex[X] = (lcursor->k[LC] * bsp_tree->k[LB] - bsp_tree->k[LC] * lcursor->k[LB]) /
				(double)(bsp_tree->k[LA] * lcursor->k[LB] - lcursor->k[LA] * bsp_tree->k[LB]);
	sep_vertex[Y] = (lcursor->k[LA] * bsp_tree->k[LC] - bsp_tree->k[LA] * lcursor->k[LC]) /
				(double)(bsp_tree->k[LA] * lcursor->k[LB] - lcursor->k[LA] * bsp_tree->k[LB]);
	return (sep_vertex);
}
