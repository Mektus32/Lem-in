/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aft_bfs_k.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:52:24 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 20:52:27 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** step 3
** поиск обратного пути по link_new
** обратный путь path начинается с последней комнаты
** в ft_path направление ссылок дублируется, тут уже не подходит такой подход
** тут надо проверять если ли ссылка из текущей комнаты на нашу //
** !!!!!!!!!!!!!!!!!!!!free(map->dist);
*/

static t_list_i	*ft_path_k(t_map *map)
{
	t_list_i	*start;
	t_list_i	*path;
	t_list_i	*tmp_i;
	int			i;
	int			f;

	path = ft_list_new_i(map->c_room);
	start = path;
	while (path && path->content != 0)
	{
		f = 1;
		i = -1;
		while ((map->c_room) * map->m > ++i && f)
		{
			if (map->dist[i] == (map->dist[path->content] - 1))
			{
				tmp_i = (ft_list_i_head(i, map->link_new))->next;
				while (tmp_i && f)
				{
					if (tmp_i->content == path->content)
					{
						f = (i > map->c_room) ? i - map->c_room : i;
						ft_list_add_back_i_one(&path, f);
						f = 0;
					}
					tmp_i = tmp_i->next;
				}
			}
		}
		path = path->next;
	}
	ft_list_revers(&start);
	free(map->dist);
	return (start);
}

/*
** находит длину пути в новом списке комнат
** заполняет список dist
** отличие от ft_bfs_2: использую запрещенные комнаты
** 		//пока есть комнаты(tmp), связанные с комнатой в очереди
**		//перезаписываем расстояние, если до этого оно было больше
*/

static int		bfs_k_path_2(t_map *map, t_list_i *order, t_list_i *all_order)
{
	t_list_i	*tmp_i;
	int			len;

	len = 0;
	while (order && !len)
	{
		tmp_i = ft_list_i_head(order->content, map->link_new)->next;
		while (tmp_i && len == 0)
		{
			if (map->dist[tmp_i->content] > map->dist[order->content] + 1
				&& (tmp_i->content != order->content))
				map->dist[tmp_i->content] = map->dist[order->content] + 1;
			if (tmp_i->content == map->c_room)
				len = map->dist[tmp_i->content];
			else if (map->dist[tmp_i->content] != -1 &&
				find_room(order, tmp_i->content) == 0)
			{
				ft_list_add_back_i_if_not(&order, tmp_i->content, all_order);
				ft_list_add_back_i_one(&all_order, tmp_i->content);
			}
			tmp_i = tmp_i->next;
		}
		order = order->next;
	}
	return (len);
}

/*
** step 3
** находит путь в графе с новыми комнатами
** находит к-ый путь, не ходя по списку использованных путей
** cant_go = -1 есди комната в списке занятых, дам ей вес -1,
** что б больше не ходить по ней
*/

t_list_i		*bfs_k_path(t_map *map, t_list_i *cant_go)
{
	int			len;
	t_list_i	*order;
	t_list_i	*all_order;
	t_list_i	*order_start;
	t_list_i	*all_order_start;

	map->dist = make_mass_cant_go(map, cant_go);
	order = ft_list_new_i(0);
	all_order = ft_list_new_i(0);
	order_start = order;
	all_order_start = all_order;
	map->dist[0] = 0;
	len = bfs_k_path_2(map, order, all_order);
	ft_free_list_i(&order_start);
	ft_free_list_i(&all_order_start);
	if (len == 0)
	{
		free(map->dist);
		if (map->two_path->content == 0)
			ft_printf("no path\n");
		return (NULL);
	}
	else
		return (ft_path_k(map));
}

static int		path_not_in(t_list_i *path_1, t_list_i *path_2)
{
	t_list_i	*path;

	while (path_2->next)
	{
		path = path_1;
		while (path->next)
		{
			if ((path_2->content == path->content) &&
				(path_2->next->content == path->next->content))
				return (0);
			path = path->next;
		}
		path_2 = path_2->next;
	}
	return (1);
}

/*
** step 4 - поиск к кратчайших путей
** c_g = cant_go;//список по которому нельзя ходить
** p_t = path_tek
*/

t_list_down		*ft_bfs_k(t_map *map, int k)
{
	t_list_i	*p_t;
	t_list_down	*path_down;
	t_list_i	*c_g;
	t_list_down	*tmp;
	int			p;

	p = 0;
	path_down = ft_list_new_down(-10);
	ft_list_add_back_down(&path_down, ft_list_new_down(0));
	tmp = path_down;
	c_g = ft_list_new_i(0);
	p_t = NULL;
	map->m = 1;
	while (p < k && (p_t = bfs_k_path(map, c_g)) && path_not_in(p_t, c_g) == 1)
	{
		ft_list_add_back_down_next(&path_down, p_t);
		tmp->down->content = ft_list_len_i(p_t);
		ft_list_add_back_i(&c_g, p_t);
		ft_free_list_i(&p_t);
		p_t = NULL;
		ft_list_add_back_down(&path_down, ft_list_new_down(-10));
		tmp = tmp->down;
		p++;
	}
	ft_free_list_i(&c_g);
	return (path_down);
}
