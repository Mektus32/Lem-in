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

t_list_i	*ft_path(t_map *map, int *dist)
{
	t_list_i *start;
	t_list_i *path;
	t_list_i *tmp_i;

	tmp_i = ft_list_i_head(map->c_room, map->link)->next;
	//обратный путь начинается с последней комнаты
	path = ft_list_new_i(map->c_room);
	//ссылка на начало, что б вернуть
	start = path;
	while (path->content != 0)// пока не придем в комнату старта ищем путь
	{
		tmp_i = (ft_list_i_head(path->content, map->link))->next;
		while (tmp_i)// ищем комнату с весом на 1 меньше, чем текущая
		{//если предыдущих ячеек несколько нам не важно, тк путь все = будет кротчайший
			if (dist[tmp_i->content] == (dist[path->content] - 1))
			{
				ft_list_add_back_i_one(&path, tmp_i->content);
				break ; // добавили одну комнату и успокоились - переходим к ней
			}
			tmp_i = tmp_i->next;
		}
		path = path->next;//переход к комнате, которую добавили
	}
	ft_list_revers(&start);
	free(dist);
	return (start);
}


void ft_bfs_2(t_map *map, t_list_i *order, t_list_i *all_order, int *dist)
{
	t_list_down	*tmp;
	t_list_i	*tmp_i;

	while (order && !(map->len_sh))
	{
		//возвращаем ссылку на комнату
		tmp = ft_list_i_head(order->content, map->link);
		tmp_i = tmp->next;//надо пропустить себя же ! ЗАПИСЬ НИЖЕ РАБОТАЕТ -2строки =)
		//tmp_i = ft_list_i_head(order->content, map->link)->next;
		//пока есть комнаты(tmp), связанные с комнатой в очереди
		//перезаписываем расстояние, если до этого оно было больше
		while (tmp_i && map->len_sh == 0)
		{
			//если в комнате, которую мы проверяем растояние от начала больше, чем от соседа которого мы можем дотянуться
			if (dist[tmp_i->content] > dist[order->content] + 1 && (tmp_i->content != order->content))
				dist[tmp_i->content] = dist[order->content] + 1;
			if (tmp_i->content == map->c_room)//нашли короткий путь, если пришли в последнюю комнату
				map->len_sh = dist[tmp_i->content]; // надо выходить из цикла while(order && !len)
			else //для каждого узла добавляем очередь соседей
			{
				ft_list_add_back_i_if_not(&order, tmp_i->content, all_order);
				ft_list_add_back_i_one(&all_order, (tmp_i->content));
			}
			tmp_i = tmp_i->next;
		}
		order = order->next;
	}

}


//0 если не найдкм ни одного пути
t_list_i	*ft_bfs(t_map *map)
{

	//длина кротчайшего пути - она наверно не нужна len внесена в структуру нам по ней все равно придется
	//выбирать количество путей от муравьев;
	t_list_i *order;
	t_list_i *all_order;

	t_list_i *order_start;
	t_list_i *all_order_start;

	int *dist; //массив интов - расстояние от старта
	dist = make_mass(map->c_room);



	//начинаем очередь в очередь добавляем все вершины, которые встретелись на пути
	order = ft_list_new_i(0);
	all_order = ft_list_new_i(0);
	order_start = order;
	all_order_start = all_order;

	// будем продолжать пока есть очередь или пока не нашли кратчайший путь (нашли комнатц энд)
//	while (order && !(map->len_sh))
//	{
//		//возвращаем ссылку на комнату
//		tmp = ft_list_i_head(order->content, map->link);
//		tmp_i = tmp->next;//надо пропустить себя же ! ЗАПИСЬ НИЖЕ РАБОТАЕТ -2строки =)
//		//tmp_i = ft_list_i_head(order->content, map->link)->next;
//		//пока есть комнаты(tmp), связанные с комнатой в очереди
//		//перезаписываем расстояние, если до этого оно было больше
//		while (tmp_i && map->len_sh == 0)
//		{
//			//если в комнате, которую мы проверяем растояние от начала больше, чем от соседа которого мы можем дотянуться
//			if (dist[tmp_i->content] > dist[order->content] + 1 && (tmp_i->content != order->content))
//				dist[tmp_i->content] = dist[order->content] + 1;
//			if (tmp_i->content == map->c_room)//нашли короткий путь, если пришли в последнюю комнату
//				map->len_sh = dist[tmp_i->content]; // надо выходить из цикла while(order && !len)
//			else //для каждого узла добавляем очередь соседей
//			{
//				ft_list_add_back_i_if_not(&order, tmp_i->content, all_order);
//				ft_list_add_back_i(&all_order, ft_list_new_i(tmp_i->content));
//
//			}
//			tmp_i = tmp_i->next;
//		}
//		order = order->next;
//	}
	ft_bfs_2(map, order, all_order, dist);
	ft_free_list_i(&order_start);
	ft_free_list_i(&all_order_start);
	//ft_free_list_i(&tmp_i_start);
	if (map->len_sh == 0) //если длина осталась нулевой
	{

		free(dist);
		printf("no path\n");
		return (NULL);
	}
	else //найдем коротуий путь (реверс) и вернем 1 оттуда
		return (ft_path(map, dist));
}

