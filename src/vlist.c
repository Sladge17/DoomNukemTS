/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:09:02 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/17 20:29:40 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vlist	*set_vlist(t_map *map)
{
	t_vlist		*vlist;
	t_vlist		*tail;
	t_vlist		*cursor;
	int			i;

	i = 0; // count of sectors
	while (i < 2)
	{
		map = init_map(i);
		tail = set_vtail(map);
		if (!i)
			vlist = tail;
		else
		{
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = create_vempty();
			cursor->next->next = tail;
		}
		cursor = tail;
		i += 1;
	}
	return (vlist);
}

t_vlist	*set_vtail(t_map *map)
{
	t_vlist	*head;
	int		i;

	head = NULL;
	i = 0;
	while (map->field[i] != '\0')
	{
		if (map->field[i] != '.' && map->field[i] != 'P')
		{
			if (!head)
			{
				head = create_vnode(i, map);
				i += 1;
				continue ;
			}
			add_vnode(&head, i, map);
		}
		i += 1;
	}
	return (head);
}

t_vlist	*create_vnode(int index, t_map *map)
{
	t_vlist	*node;

	node = (t_vlist *)malloc(sizeof(t_vlist));
	node->data = (int)map->field[index] - 0x30;
	node->index = index;
	node->crd[X] = index % map->width;
	node->crd[Y] = index / map->width;
	node->next = NULL;
	return (node);
}

t_vlist	*create_vempty()
{
	t_vlist	*node;

	node = (t_vlist *)malloc(sizeof(t_vlist));
	node->data = 0;
	node->index = 0;
	node->crd[X] = 0;
	node->crd[Y] = 0;
	node->next = NULL;
	return (node);
}

void	add_vnode(t_vlist **head, int index, t_map *map)
{
	t_vlist	*tmpnode;
	t_vlist	*cursor;

	tmpnode = create_vnode(index, map);
	cursor = *head;
	if (cursor->data > tmpnode->data)
	{
		tmpnode->next = cursor;
		*head = tmpnode;
		return ;
	}
	
	while (cursor->next && !(cursor->data < tmpnode->data && cursor->next->data > tmpnode->data))
		cursor = cursor->next;

	if (cursor->next)
		tmpnode->next = cursor->next;
	cursor->next = tmpnode;
}

void	del_vlist(t_vlist **head)
{
	t_vlist		*cursor;

	while ((*head)->next)
	{
		cursor = *head;
		while (cursor->next->next)
			cursor = cursor->next;
		free(cursor->next);
		cursor->next = NULL;
	}
	free(*head);
}