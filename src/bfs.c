/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:04:37 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/14 15:04:38 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** путь, один от начала до конца по массиву расстояний от комнаты старта
** находит обратный путь path и реверсит его
** start - ссылка на начало, что б вернуть
** tmp_i - связи текущей комнаты, ищем в них комнату с весом,
** меньшим чем в текущей на 1
** если таких ячеек несколько нам не важно, тк путь все = будет кротчайший
*/

t_list_i	*ft_path(t_map *map)
{
	t_list_i	*start;
	t_list_i	*path;
	t_list_i	*tmp_i;

	path = ft_list_new_i(map->c_r);
	start = path;
	while (path->cnt != 0)
	{
		tmp_i = (i_head(path->cnt, map->link))->next;
		while (tmp_i)
		{
			if (map->dist[tmp_i->cnt] == (map->dist[path->cnt] - 1))
			{
				list_add_i1(&path, tmp_i->cnt);
				break ;
			}
			tmp_i = tmp_i->next;
		}
		path = path->next;
	}
	ft_list_revers(&start);
	free(map->dist);
	return (start);
}

/*
** заполняет массив минимальных растояний от старта до текущей комнаты
** ходим только по тем комнатам, которых не было в all_order,
** что б не проходить несколько раз
** пока есть комнаты(tmp), связанные с комнатой в очереди
** перезаписываем расстояние, если до этого оно было больше
** если в комнате, которую мы проверяем растояние от начала больше,
** чем от соседа которого мы можем дотянуться
** нашли короткий путь, если пришли в последнюю комнату
** надо выходить из цикла while(order && !len)
** для каждого узла добавляем очередь соседей
*/

void		ft_bfs_2(t_map *map, t_list_i *order, t_list_i *all_order)
{
	t_list_i	*tmp_i;

	while (order && !(map->len_sh))
	{
		tmp_i = i_head(order->cnt, map->link)->next;
		while (tmp_i && !map->len_sh)
		{
			if (map->dist[tmp_i->cnt] > map->dist[order->cnt] + 1 &&
				(tmp_i->cnt != order->cnt))
				map->dist[tmp_i->cnt] = map->dist[order->cnt] + 1;
			if (tmp_i->cnt == map->c_r)
				map->len_sh = map->dist[tmp_i->cnt];
			else
			{
				ft_list_add_back_i_if_not(&order, tmp_i->cnt, all_order);
				ft_list_add_back_i_if_not(&all_order, tmp_i->cnt, all_order);
			}
			tmp_i = tmp_i->next;
		}
		order = order->next;
	}
}

/*
** bfs для одного пути
** dist - массив интов - расстояние от старта
** ft_bfs_2 - заполняет массив dist, изменяет map->len_sh на длину пути,
** если он есть
** ft_path - возвращает путь list_i
** начинаем очередь в очередь добавляем все вершины, которые встретелись на пути
** если длина осталась нулевой !!! //free(dist);
** найдем коротуий путь (реверс) и вернем 1 оттуда
*/

t_list_i	*ft_bfs(t_map *map)
{
	t_list_i	*order;
	t_list_i	*all_order;
	t_list_i	*order_start;
	t_list_i	*all_order_start;

	map->dist = make_mass(map->c_r);
	order = ft_list_new_i(0);
	all_order = ft_list_new_i(0);
	order_start = order;
	all_order_start = all_order;
	ft_bfs_2(map, order, all_order);
	ft_free_list_i(&order_start);
	ft_free_list_i(&all_order_start);
	if (map->len_sh == 0)
	{
		printf("no path\n");
		return (NULL);
	}
	else
		return (ft_path(map));
}
