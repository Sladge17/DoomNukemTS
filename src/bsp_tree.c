/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/15 13:13:55 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// t_bsp	*set_tree(t_llist *llist)
// {
// 	t_bsp		*bsp_tree;
// 	double		*vertex[2];
	
// 	vertex[0] = (double *)malloc(sizeof(double) * 2);
// 	vertex[1] = (double *)malloc(sizeof(double) * 2);
// 	bsp_tree = NULL;
// 	while (llist)
// 	{
// 		vertex[0][X] = llist->crd[0][X];
// 		vertex[0][Y] = llist->crd[0][Y];
// 		vertex[1][X] = llist->crd[1][X];
// 		vertex[1][Y] = llist->crd[1][Y];
// 		if (!bsp_tree)
// 		{
// 			bsp_tree = create_bspnode(vertex[0], vertex[1], llist);
// 			llist = llist->next;
// 			continue ;
// 		}
// 		add_bspnode(bsp_tree, llist, vertex[0], vertex[1]);
// 		llist = llist->next;
// 	}
// 	free(vertex[0]);
// 	free(vertex[1]);
// 	return (bsp_tree);
// }

t_bsp	*set_tree(t_llist *llist)
{
	t_bsp		*bsp_tree;
	int			llen;
	t_llist		*slicer;

	llen = set_llen(llist);

	if (llen == 1)
	{
		bsp_tree = create_bspnode(llist);
		free(llist);
		return (bsp_tree);
	}
	
	slicer = set_slicer(&llist, llen);

		// printf("%f %f\n", slicer->crd[0][X], slicer->crd[0][Y]);
		// printf("%f %f\n", slicer->crd[1][X], slicer->crd[1][Y]);
		// printf("\n----\n");

		// t_llist	*crs = llist;
		// while (crs)
		// {
		// 	printf("%f %f\n", crs->crd[0][X], crs->crd[0][Y]);
		// 	printf("%f %f\n", crs->crd[1][X], crs->crd[1][Y]);
		// 	printf("\n");
		// 	crs = crs->next;
		// }
		// printf("\n----\n");
		
	t_llist	*front = NULL;
	t_llist	*front_crs;
	
	t_llist	*back = NULL;
	t_llist	*back_crs;

	double	*sep_vertex;
	t_llist	*linsert;

	// t_llist	*cursor = llist;
	while (llist)
	{
		if (slicer->k[LA] * llist->crd[0][X] + slicer->k[LB] * llist->crd[0][Y] <= -slicer->k[LC] &&
			slicer->k[LA] * llist->crd[1][X] + slicer->k[LB] * llist->crd[1][Y] <= -slicer->k[LC])
		{
			if (!front)
			{
				front = llist;
				front_crs = llist;
				llist = llist->next;
				// front_crs->next = NULL; // maybe not need 
			}
			else
			{
				front_crs->next = llist;
				front_crs = front_crs->next;
				llist = llist->next;
				// front_crs->next = NULL; // maybe not need 
			}
			continue ;
		}
		if (slicer->k[LA] * llist->crd[0][X] + slicer->k[LB] * llist->crd[0][Y] >= -slicer->k[LC] &&
			slicer->k[LA] * llist->crd[1][X] + slicer->k[LB] * llist->crd[1][Y] >= -slicer->k[LC])
		{
			if (!back)
			{
				back = llist;
				back_crs = llist;
				llist = llist->next;
				// back_crs->next = NULL; // maybe not need 
			}
			else
			{
				back_crs->next = llist;
				back_crs = back_crs->next;
				llist = llist->next;
				// back_crs->next = NULL; // maybe not need 
			}
			continue ;
		}
		sep_vertex = sep_lnode(llist, slicer);
		
		linsert = copy_lnode(llist);
		
		llist->crd[1][X] = sep_vertex[X];
		llist->crd[1][Y] = sep_vertex[Y];
		linsert->crd[0][X] = sep_vertex[X];
		linsert->crd[0][Y] = sep_vertex[Y];
		free(sep_vertex);

		linsert->next = llist->next;
		llist->next = linsert;
	}

	if (front)
		front_crs->next = NULL;
	if (back)
		back_crs->next = NULL;

	// printf("print front\n");
	// front_crs = front;
	// while (front_crs)
	// {
	// 	printf("%f %f\n", front_crs->crd[0][X], front_crs->crd[0][Y]);
	// 	printf("%f %f\n", front_crs->crd[1][X], front_crs->crd[1][Y]);
	// 	printf("\n");
	// 	front_crs = front_crs->next;
	// }

	
	// printf("print back\n");
	// back_crs = back;
	// while (back_crs)
	// {
	// 	printf("%f %f\n", back_crs->crd[0][X], back_crs->crd[0][Y]);
	// 	printf("%f %f\n", back_crs->crd[1][X], back_crs->crd[1][Y]);
	// 	printf("\n");
	// 	back_crs = back_crs->next;
	// }

	bsp_tree = create_bspnode(slicer);
	free(slicer);

	if (front)
		bsp_tree->front = set_tree(front);
	if (back)
		bsp_tree->back = set_tree(back);

	// if (llist->next)
	// {}
		
		// if (!bsp_tree)
		// {
		// 	bsp_tree = create_bspnode(vertex[0], vertex[1], slicer);
		// 	continue ;
		// }
		// add_bspnode(bsp_tree, slicer, vertex[0], vertex[1]);
	// free(vertex[0]);
	// free(vertex[1]);

	// exit(0);
	
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


t_llist	*set_slicer(t_llist **llist, int llen)
{
	t_llist	*slicer;
	t_llist	*cursor;
	// int		llen;
	int		*score;
	int		j;
	t_llist	*temp;
	int		i;
	int		front;
	int		back;

	// cursor = *llist;
	// llen = 0;
	// while (cursor)
	// {
	// 	llen += 1;
	// 	cursor = cursor->next;
	// }

	score = (int *)malloc(sizeof(int) * llen);

	slicer = *llist;
	j = 0;
	while (j < llen)
	{
		temp = slicer->next;
		slicer->next = NULL;
		cursor = temp;
		i = 0;
		front = 0;
		back = 0;
		while (i < llen - 1)
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
		score[j] = abs(front - back);
		
		if (cursor)
			cursor->next = slicer;
			
		slicer = temp;
		j += 1;
	}

	i = 0;
	j = 1;
	while (j < llen)
	{
		if (score[j] < score[i])
			i = j;
		j += 1;
	}
	free(score);
	if (!i)
	{
		slicer = *llist;
		*llist = (*llist)->next;
	}
	else
	{
		cursor = *llist;
		j = 0;
		while (j < i - 1)
		{
			cursor = cursor->next;
			j += 1;
		}
		slicer = cursor->next;
		cursor->next = cursor->next->next;
	}
	return (slicer);
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


// void	add_bspnode(t_bsp *bsp_tree, t_llist *lcursor, double *vertex_0, double *vertex_1)
// {
// 	t_bsp	*bsp_node;
// 	double	*sep_vertex;

// 	if (bsp_tree->k[LA] * vertex_0[X] + bsp_tree->k[LB] * vertex_0[Y] <= -bsp_tree->k[LC] &&
// 		bsp_tree->k[LA] * vertex_1[X] + bsp_tree->k[LB] * vertex_1[Y] <= -bsp_tree->k[LC])
// 	{
// 		if (bsp_tree->front)
// 		{
// 			add_bspnode(bsp_tree->front, lcursor, vertex_0, vertex_1);
// 			return ;
// 		}
// 		bsp_node = create_bspnode(vertex_0, vertex_1, lcursor);
// 		bsp_tree->front = bsp_node;
// 		return ;
// 	}
// 	if (bsp_tree->k[LA] * vertex_0[X] + bsp_tree->k[LB] * vertex_0[Y] >= -bsp_tree->k[LC] &&
// 		bsp_tree->k[LA] * vertex_1[X] + bsp_tree->k[LB] * vertex_1[Y] >= -bsp_tree->k[LC])
// 	{
// 		if (bsp_tree->back)
// 		{
// 			add_bspnode(bsp_tree->back, lcursor,  vertex_0, vertex_1);
// 			return ;
// 		}
// 		bsp_node = create_bspnode(vertex_0, vertex_1, lcursor);
// 		bsp_tree->back = bsp_node;
// 		return ;
// 	}
// 	sep_vertex = sep_lnode(bsp_tree, lcursor);
// 	add_bspnode(bsp_tree, lcursor, vertex_0, sep_vertex);
// 	add_bspnode(bsp_tree, lcursor, sep_vertex, vertex_1);
// 	free(sep_vertex);
// }

// double	*sep_lnode(t_bsp *bsp_tree, t_llist *lcursor)
double	*sep_lnode(t_llist *llist, t_llist *slicer)
{
	double	*sep_vertex;

	sep_vertex = (double *)malloc(sizeof(double) * 2);
	sep_vertex[X] = (slicer->k[LC] * llist->k[LB] - llist->k[LC] * slicer->k[LB]) /
				(double)(llist->k[LA] * slicer->k[LB] - slicer->k[LA] * llist->k[LB]);
	sep_vertex[Y] = (slicer->k[LA] * llist->k[LC] - llist->k[LA] * slicer->k[LC]) /
				(double)(llist->k[LA] * slicer->k[LB] - slicer->k[LA] * llist->k[LB]);
	return (sep_vertex);
}
