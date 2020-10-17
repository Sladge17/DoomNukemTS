/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:28:58 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/17 13:37:48 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_tree(t_bsp *bsp_tree)
{
	printf("%f %f\n", bsp_tree->crd[0][X], bsp_tree->crd[0][Y]);
	printf("%f %f\n", bsp_tree->crd[1][X], bsp_tree->crd[1][Y]);
	printf("\n");

	if (bsp_tree->front)
	{
		printf("go to front\n");
		print_tree(bsp_tree->front);
		printf("return from front\n");
	}
	if (bsp_tree->back)
	{
		printf("go to back\n");
		print_tree(bsp_tree->back);
		printf("return from back\n");
	}
}