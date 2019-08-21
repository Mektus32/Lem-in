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

int				add_path_i(t_map *map, t_list_i *path, int i)
{
	t_list_i	*tmp_i;

	tmp_i = (i_head(i, map->l_new))->next;
	while (tmp_i)
	{
		if (tmp_i->cnt == path->cnt)
		{
			list_add_i1(&path, (i > map->c_r) ? i - map->c_r : i);
			return (0);
		}
		tmp_i = tmp_i->next;
	}
	return (1);
}

/*
** step 3
** поиск обратного пути по l_new
** обратный путь path начинается с последней комнаты
** в ft_path направление ссылок дублируется, тут уже не подходит такой подход
** тут надо проверять если ли ссылка из текущей комнаты на нашу //
** !!!!!!!!!!!!!!!!!!!!free(map->dist);
*/

static t_list_i	*ft_path_k(t_map *map)
{
	t_list_i	*start;
	t_list_i	*path;
	int			i;
	int			f;

	path = ft_list_new_i(map->c_r);
	start = path;
	while (path && path->cnt != 0)
	{
		f = 1;
		i = -1;
		while ((map->c_r) * map->m > ++i && f)
		{
			if (map->dist[i] == (map->dist[path->cnt] - 1))
				f = add_path_i(map, path, i);
			else
				f = 1;
		}
		path = path->next;
	}
	free(map->dist);
	ft_list_revers(&start);
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
		tmp_i = i_head(order->cnt, map->l_new)->next;
		while (tmp_i && !len)
		{
			if (map->dist[tmp_i->cnt] > map->dist[order->cnt] + 1 && (tmp_i->cnt != order->cnt))
				map->dist[tmp_i->cnt] = map->dist[order->cnt] + 1;
			if (tmp_i->cnt == map->c_r)
				len = map->dist[tmp_i->cnt];
			else if (map->dist[tmp_i->cnt] != -1 )
			{
				ft_list_add_back_i_if_not(&order, tmp_i->cnt, all_order);
				ft_list_add_back_i_if_not(&all_order, tmp_i->cnt, all_order);
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
	path_down = list_new_down(-10);
	list_add_down(&path_down, list_new_down(0));
	tmp = path_down;
	c_g = ft_list_new_i(0);
	p_t = NULL;
	while (p < k && (p_t = bfs_k_path(map, c_g)) && !p_t->cnt)
	{
		ft_list_add_back_down_next(&path_down, p_t);
		tmp->down->content = ft_list_len_i(p_t);
		ft_list_add_back_i(&c_g, p_t);
		ft_free_list_i(&p_t);
		list_add_down(&path_down, list_new_down(-10));
		tmp = tmp->down;
		p++;
	}
	ft_free_list_i(&c_g);
	return (path_down);
}
