/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alist_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 17:25:57 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/17 17:25:59 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list_path	*ft_list_new_path(int num_ant, char *name, t_list_path *prev)
{
	t_list_path	*list;

	if (!(list = (t_list_path*)malloc(sizeof(t_list_path))))
		return (NULL);
	list->num_ant = num_ant;
	list->name_room = name;
	list->next = NULL;
	list->prev = prev;
	return (list);
}

t_list_path	*ft_list_add_back_path(t_list_path **head, int num_ant, char *name)
{
	t_list_path	*list;
	t_list_path	*tmp;

	if (!head)
		return (NULL);
	list = *head;
	if (list)
	{
		tmp = NULL;
		while (list->next)
		{
			tmp = list;
			list = list->next;
		}
		if (tmp && tmp->next)
			list->next = ft_list_new_path(num_ant, name, tmp->next);
		else
			list->next = ft_list_new_path(num_ant, name, NULL);
	}
	else
	{
		list = ft_list_new_path(num_ant, name, NULL);
		*head = list;
	}
	return (list);
}

/*
** массив из n путей
*/

t_list_path	*path_n_mass(int c_path)
{
	t_list_path	*tmp_path;
	int			i;

	tmp_path = (t_list_path*)malloc(sizeof(t_list_path) * (c_path));
	i = 0;
	while (i < c_path)
	{
		tmp_path[i].name_room = 0;
		tmp_path[i].next = NULL;
		tmp_path[i].num_ant = 0;
		tmp_path[i].prev = NULL;
		i++;
	}
	return (tmp_path);
}

/*
** заполнение i-ого элемента массива двухсвязного списка
** для каждой комнаты в итом пути запишем связи на след и пред комнату
** всем комнатам раздадим 0 муравьев
** d_i = d[i] - длина каждого пути
** tmp_i - текущий путь без старта
*/

void		path_add_i(t_list_path *path_n, int d_i, t_map *map,
	t_list_i *tmp_i)
{
	int	k;

	k = 0;
	while (k < d_i && tmp_i)
	{
		ft_list_add_back_path(&path_n, 0, ft_name_room(map->rooms, tmp_i->cnt));
		tmp_i = tmp_i->next;
		k++;
	}
}
