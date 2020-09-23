/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 20:33:12 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/23 20:33:58 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "main.h"

 t_bsp	*set_tree(t_map *map)
{
	t_bsp	*root;
	int		i;

	root = NULL;
	i = 0;
	while (map->field[i] != '\0')
	{
		if (map->field[i] != '.' && map->field[i] != 'P')
		{
			if (!root)
			{
				root = create_node(i, map);
				i += 1;
				continue ;
			}
			add_node(root, i, map);
		}
		i += 1;
	}
	return (root);
}

t_bsp	*create_node(int index, t_map *map)
{
	t_bsp	*node;
	int		scale = 30; // <-- ONLY for draw mini_map

	node = (t_bsp *)malloc(sizeof(t_bsp));
	node->index = (int)map->field[index] - 0x30;
	node->crd[X] = index % map->width * scale;
	node->crd[Y] = index / map->width * scale;
	node->front = NULL;
	node->back = NULL;
	return (node);
}

void	add_node(t_bsp *root, int index, t_map *map)
{
	while (1)
	{
		if ((int)map->field[index] - 0x30 < root->index)
		{
			if (!(root->back))
			{
				root->back = create_node(index, map);
				return ;
			}
			root = root->back;
		}
		else
		{
			if (!(root->front))
			{
				root->front = create_node(index, map);
				return ;
			}
			root = root->front;
		}
	}
}