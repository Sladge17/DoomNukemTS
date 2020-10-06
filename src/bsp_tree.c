/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/06 19:26:45 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// t_bsp	*set_tree(t_vlist *vlist, t_llist *llist)
// {
// 	t_bsp		*bsp_tree;
// 	t_vlist		*vcursor;
// 	t_llist		*lcursor;
// 	double		vertex[2][2];

// 	bsp_tree = NULL;
	
// 	vcursor = vlist;
// 	lcursor = llist;
// 	vertex[0][X] = vcursor->crd[X];
// 	vertex[0][Y] = vcursor->crd[Y];
// 	vertex[1][X] = vcursor->next->crd[X];
// 	vertex[1][Y] = vcursor->next->crd[Y];
	
// 	while (lcursor)
// 	{
// 		if (!bsp_tree)
// 		{
// 			bsp_tree = create_bspnode(&vertex[0][0], &vertex[1][0], llist);
// 			vcursor = vcursor->next;
// 			lcursor = lcursor->next;
// 		}
		
// 		add_bspnode(bsp_tree, vcursor, llist)
		
		
// 	}
// 	return (bsp_tree);
// }

// t_bsp	*create_bspnode(double *vertex_0, double *vertex_1, t_llist *llist)
// {
// 	t_bsp	*bsp_node;

// 	bsp_node = (t_bsp *)malloc(sizeof(t_bsp));
// 	bsp_node->crd[0][X] = vertex_0[X];
// 	bsp_node->crd[0][Y] = vertex_0[Y];
// 	bsp_node->crd[1][X] = vertex_1[X];
// 	bsp_node->crd[1][Y] = vertex_1[Y];

// 	bsp_node->proj[X] = vertex_1[X] - vertex_0[X];
// 	bsp_node->proj[Y] = vertex_1[Y] - vertex_0[Y];
// 	bsp_node->len = sqrt(bsp_node->proj[X] * bsp_node->proj[X] + bsp_node->proj[Y] * bsp_node->proj[Y]);
// 	bsp_node->pivot[X] = vertex_0[X] + bsp_node->proj[X] / 2;
// 	bsp_node->pivot[Y] = vertex_0[Y] + bsp_node->proj[Y] / 2;

// 	bsp_node->direct = llist->direct;
// 	bsp_node->normal = llist->normal;
// 	bsp_node->k[LA] = llist->k[LA];
// 	bsp_node->k[LB] = llist->k[LB];
// 	bsp_node->k[LC] = llist->k[LC];

// 	bsp_node->front = NULL;
// 	bsp_node->back = NULL;
	
// 	return (bsp_node);
// }


// void	add_bspnode(t_bsp *bsp_tree, t_vlist *vcursor, t_llist *llist)
// {
// 	t_bsp	*bsp_node;
// 	double	vertex[2][2];

// 	// if (slicer->k[LA] * vertex_0->crd[X] + slicer->k[LB] * vertex_0->crd[Y] <= -slicer->k[LC] &&
// 	// 	slicer->k[LA] * vertex_1->crd[X] + slicer->k[LB] * vertex_1->crd[Y] <= -slicer->k[LC])
// 	if (llist->k[LA] * vertex_0->crd[X] + llist->k[LB] * vertex_0->crd[Y] <= -llist->k[LC] &&
// 		llist->k[LA] * vertex_1->crd[X] + llist->k[LB] * vertex_1->crd[Y] <= -llist->k[LC])
// 	{
// 		if (bsp_tree->front)
// 			// add_node(vertex_0, vertex_1, slicer->front);
// 			add_bspnode(bsp_tree->front, vcursor, llist->next);
// 		else
// 		{
// 			vertex[0][X] = vcursor->crd[X];
// 			vertex[0][Y] = vcursor->crd[Y];
// 			vertex[1][X] = vcursor->next->crd[X];
// 			vertex[1][Y] = vcursor->next->crd[Y];
// 			bsp_node = create_bspnode(&vertex[0][0], &vertex[1][0], llist);
// 			bsp_tree->front = bsp_node;
// 			printf("Add to front\n");
// 		}
// 		return (1);
// 	}
// 	if (llist->k[LA] * vertex_0->crd[X] + llist->k[LB] * vertex_0->crd[Y] >= -llist->k[LC] &&
// 		llist->k[LA] * vertex_1->crd[X] + llist->k[LB] * vertex_1->crd[Y] >= -llist->k[LC])
// 	{
// 		if (bsp_tree->back)
// 			add_node(vertex_0, vertex_1, slicer->back);
// 		else
// 		{
// 			bsp_node = create_node(vertex_0, vertex_1);
// 			slicer->back = bsp_node;
// 		printf("Add to back\n");
// 		}
// 		return (1);
// }




t_bsp	*set_tree(t_vlist *vlist)
{
	t_bsp		*bsp_tree;
	t_vlist		*vcursor;
	// t_llist		*lcursor;

	bsp_tree = NULL;
	vcursor = vlist;
	// lcursor = llist;
	while (1)
	{
		while (vcursor->next && vcursor->next->data)
		{
			if (!bsp_tree)
			{
				bsp_tree = create_node(vcursor, vcursor->next);
				vcursor = vcursor->next;
				continue ;
			}
			// add_node(vcursor, vcursor->next, bsp_tree);
			while (!(add_node(vcursor, vcursor->next, bsp_tree))) //MAYBE IF
				sep_vnode(vcursor, vcursor->next, bsp_tree);
			vcursor = vcursor->next;
		}
		// add_node(vcursor, vlist, bsp_tree);
		if (!(add_node(vcursor, vlist, bsp_tree)))  //MAYBE WHILE
		{
			sep_vnode_end(vcursor, vlist, bsp_tree);
			add_node(vcursor, vcursor->next, bsp_tree);
			vcursor = vcursor->next;
			add_node(vcursor, vlist, bsp_tree);
		}
		if (!vcursor->next)
			return (bsp_tree);
		vlist = vcursor->next->next;
		vcursor = vlist;
	}
	return (bsp_tree);
}


void	sep_vnode(t_vlist *vertex_0, t_vlist *vertex_1, t_bsp *slicer)
{

	double		k[3];
	// int		k[3];

	k[LA] = vertex_0->crd[Y] - vertex_1->crd[Y];
	k[LB] = vertex_1->crd[X] - vertex_0->crd[X];
	k[LC] = vertex_0->crd[X] * vertex_1->crd[Y] - vertex_1->crd[X] * vertex_0->crd[Y];

	double	sep_crd[2];
	// int		sep_crd[2];
	

	sep_crd[X] = (k[LC] * slicer->k[LB] - slicer->k[LC] * k[LB]) /
				(double)(slicer->k[LA] * k[LB] - k[LA] * slicer->k[LB]);
	sep_crd[Y] = (k[LA] * slicer->k[LC] - slicer->k[LA] * k[LC]) /
				(double)(slicer->k[LA] * k[LB] - k[LA] * slicer->k[LB]);

	// printf("%f %f\n", sep_crd[X], sep_crd[Y]);
	// exit(0);

	
	t_vlist		*insert_vnode;
	insert_vnode = (t_vlist *)malloc(sizeof(t_vlist));
	insert_vnode->data = vertex_0->data;
	insert_vnode->crd[X] = sep_crd[X];
	insert_vnode->crd[Y] = sep_crd[Y];
	insert_vnode->next = vertex_1;
	vertex_0->next = insert_vnode;
	
	// printf("%f %f\n", insert_vnode->crd[X], insert_vnode->crd[Y]);
	// exit(0);
}

void	sep_vnode_end(t_vlist *vertex_0, t_vlist *vertex_1, t_bsp *slicer)
{

	double		k[3];
	// int		k[3];

	k[LA] = vertex_0->crd[Y] - vertex_1->crd[Y];
	k[LB] = vertex_1->crd[X] - vertex_0->crd[X];
	k[LC] = vertex_0->crd[X] * vertex_1->crd[Y] - vertex_1->crd[X] * vertex_0->crd[Y];

	double		sep_crd[2];
	// int		sep_crd[2];

	sep_crd[X] = (k[LC] * slicer->k[LB] - slicer->k[LC] * k[LB]) /
				(double)(slicer->k[LA] * k[LB] - k[LA] * slicer->k[LB]);
	sep_crd[Y] = (k[LA] * slicer->k[LC] - slicer->k[LA] * k[LC]) /
				(double)(slicer->k[LA] * k[LB] - k[LA] * slicer->k[LB]);

	
	t_vlist		*insert_vnode;
	insert_vnode = (t_vlist *)malloc(sizeof(t_vlist));
	insert_vnode->data = vertex_0->data;
	insert_vnode->crd[X] = sep_crd[X];
	insert_vnode->crd[Y] = sep_crd[Y];
	insert_vnode->next = NULL;
	vertex_0->next = insert_vnode;
}

t_bsp	*create_node(t_vlist *vertex_0, t_vlist *vertex_1)
{
	t_bsp	*node;

	node = (t_bsp *)malloc(sizeof(t_bsp));

	node->index[0] = vertex_0->index;
	node->index[1] = vertex_1->index;
	node->crd[0][X] = vertex_0->crd[X];
	node->crd[0][Y] = vertex_0->crd[Y];
	node->crd[1][X] = vertex_1->crd[X];
	node->crd[1][Y] = vertex_1->crd[Y];
	
	node->proj[X] = vertex_1->crd[X] - vertex_0->crd[X];
	node->proj[Y] = vertex_1->crd[Y] - vertex_0->crd[Y];
	node->len = sqrt(node->proj[X] * node->proj[X] + node->proj[Y] * node->proj[Y]);
	node->pivot[X] = vertex_0->crd[X] + node->proj[X] / (double)2;
	node->pivot[Y] = vertex_0->crd[Y] + node->proj[Y] / (double)2;
	node->direct = atan2((double)node->proj[Y], (double)node->proj[X]);
	node->normal = node->direct - M_PI_2;
	
	node->k[LA] = vertex_0->crd[Y] - vertex_1->crd[Y];
	node->k[LB] = vertex_1->crd[X] - vertex_0->crd[X];
	node->k[LC] = vertex_0->crd[X] * vertex_1->crd[Y] - vertex_1->crd[X] * vertex_0->crd[Y];

	node->front = NULL;
	node->back = NULL;
	return (node);
}


char	add_node(t_vlist *vertex_0, t_vlist *vertex_1, t_bsp *slicer)
{
	t_bsp	*node;

	if (slicer->k[LA] * vertex_0->crd[X] + slicer->k[LB] * vertex_0->crd[Y] <= -slicer->k[LC] &&
		slicer->k[LA] * vertex_1->crd[X] + slicer->k[LB] * vertex_1->crd[Y] <= -slicer->k[LC])
	{
		if (slicer->front)
			add_node(vertex_0, vertex_1, slicer->front);
		else
		{
			node = create_node(vertex_0, vertex_1);
			slicer->front = node;
			printf("Add to front\n");
		}
		return (1);
	}
	if (slicer->k[LA] * vertex_0->crd[X] + slicer->k[LB] * vertex_0->crd[Y] >= -slicer->k[LC] &&
		slicer->k[LA] * vertex_1->crd[X] + slicer->k[LB] * vertex_1->crd[Y] >= -slicer->k[LC])
	{
		if (slicer->back)
			add_node(vertex_0, vertex_1, slicer->back);
		else
		{
			node = create_node(vertex_0, vertex_1);
			slicer->back = node;
		printf("Add to back\n");
		}
		return (1);
	}
	// return (0);

	node = create_node(vertex_0, vertex_1);

	double		sep_crd[2];

	sep_crd[X] = (node->k[LC] * slicer->k[LB] - slicer->k[LC] * node->k[LB]) /
				(double)(slicer->k[LA] * node->k[LB] - node->k[LA] * slicer->k[LB]);
	sep_crd[Y] = (node->k[LA] * slicer->k[LC] - slicer->k[LA] * node->k[LC]) /
				(double)(slicer->k[LA] * node->k[LB] - node->k[LA] * slicer->k[LB]);

	// printf("%d %d\n", sep_crd[X], sep_crd[Y]);
	// exit(0);
	return (0);
}
