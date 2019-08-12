#include "lem_in.h"


/*обход*/
t_list_i	*ft_path_k(t_map *map, int *dist)
{
	t_list_i *start;
	t_list_i *path;
	t_list_i *tmp_i;
	int tmp_n;
	int i;
	int f;
	//обратный путь начинается с последней комнаты
	path = ft_list_new_i(map->c_room);
	start = path; /*не потерять ссылку на начало*/
	while (path && path->content != 0)// пока не придем в комнату старта ищем путь
	{
		f = 1;
		i = 0;
		while ((map->c_room) * 2 > i && f)
		{

			if (dist[i] == (dist[path->content] - 1))
			{
				//есть ли из i-ой комнаты ссылка на нас?
				tmp_n = (ft_list_i_head(i, map->link_new))->content;
				tmp_i = (ft_list_i_head(i, map->link_new))->next;
				while (tmp_i)
				{
					if (tmp_i->content == path->content)
					{
						ft_list_add_back_i_one(&path, tmp_n);
						//ft_free_list_i(&tmp_n);
						f = 0;
						break ;
					}
					tmp_i = tmp_i->next;
				}
			}
			i++;
		}
		path = path->next;/*переход к комнате, которую добавили*/
	}
	path = start;
	while(path) /*если это созаданная комната*/
	{
		if (path->content > map->c_room)
			path->content -= map->c_room;
		path = path->next;
	}
	ft_list_revers(&start);
	free(dist);
	return (start);
}

int bfs_k_path_2(t_map *map, t_list_i *order, t_list_i *all_order, int *dist)
{
	t_list_i 	*tmp_i;
	int 		len;
	int f;

	f = 1;

	len = 0;
	while (order && !len && f)
	{
		f = 1;
		tmp_i = ft_list_i_head(order->content, map->link_new)->next;
		//пока есть комнаты(tmp), связанные с комнатой в очереди
		//перезаписываем расстояние, если до этого оно было больше
		while (tmp_i && len == 0 && f)
		{
			//если в комнате, которую мы проверяем растояние от начала больше, чем от соседа которого мы можем дотянуться
			if (dist[tmp_i->content] > dist[order->content] + 1 && (tmp_i->content != order->content))
				dist[tmp_i->content] = dist[order->content] + 1;
			if (tmp_i->content == map->c_room)//нашли короткий путь, если пришли в последнюю комнату
			{
				len = dist[tmp_i->content]; // надо выходить из цикла while(order && !len)
				f = 0;
			}
				//для каждого узла добавляем очередь соседей если нет в запрещеном списке
			else if (dist[tmp_i->content] != -1 && find_room(order ,tmp_i->content) == 0)
			{
				ft_list_add_back_i_if_not(&order, tmp_i->content, all_order);//ft_list_add_back_i(&order, ft_list_new_i(tmp_i->content));
				ft_list_add_back_i_one(&all_order, tmp_i->content);

			}
			tmp_i = tmp_i->next;
		}
		order = order->next;
	}
//	ft_free_list_down(&map->link_new);
	return(len);



}

//находит к-ый путь, не ходя по списку использованных путей
t_list_i 		*bfs_k_path(t_map *map, t_list_i *cant_go)
{
	int			i;
	int len;
	int 		*dist; /*массив расстояний от комнаты старта*/
	t_list_i 	*order;
	t_list_i *all_order;
	t_list_i *order_start;
	t_list_i *all_order_start;


	dist = make_mass(2*map->c_room);
	i = 0;
	//есди комната в списке занятых, дам ей вес -1, что б больше не ходить по ней
	while (i < 2*map->c_room)
	{
		if (find_room(cant_go, i) && i != 0 && i != map->c_room)
			dist[i] = -1;
		i++;
	}
	//начинаем очередь в очередь добавляем все вершины, которые встретелись на пути
	order = ft_list_new_i(0);
	all_order = ft_list_new_i(0);
	order_start = order;
	all_order_start = all_order;
	dist[0] = 0;
	// будем продолжать пока есть очередь или пока не нашли кратчайший путь (нашли комнатц энд)
	len = bfs_k_path_2(map, order, all_order, dist);
	ft_free_list_i(&order_start);
	ft_free_list_i(&all_order_start);
	if (len == 0) //если длина осталась нулевой
	{
		free (dist);
		if (map->two_path->content == 0)
			ft_printf("no path\n");
		return (NULL);
	}
	else //найдем коротуий путь (реверс) и вернем 1 оттуда
		return (ft_path_k(map, dist));
}

static  int path_not_in(t_list_i *path_1, t_list_i *path_2)
{
	t_list_i *path;


	while(path_2->next)
	{
		path = path_1;
		while (path->next)
		{
			if ((path_2->content == path->content) && (path_2->next->content == path->next->content))
				return (0);
			path = path->next;
		}
		path_2 = path_2->next;
	}
	// если не в списке 1
	return (1);
}

//поиск к кратчайших путей
t_list_down		*ft_bfs_k(t_map *map, int k)
{
	t_list_i	*path_tek;
	t_list_down *path_down;
	t_list_i	*cant_go;//список по которому нельзя ходить
	t_list_down	*tmp;
	int p;
	p = 0;
	path_down = ft_list_new_down(-10);//(t_list_down*)malloc(sizeof(t_list_down));
	ft_list_add_back_down(&path_down, ft_list_new_down(0));//path_down->down = (t_list_down*)malloc(sizeof(t_list_down));
	tmp = path_down;
	//path_down->down->next = NULL;
	cant_go = ft_list_new_i(0);//cant_go = (t_list_i*)malloc(sizeof(t_list_i));
	//ft_pri_cop(map);
	path_tek = NULL;
	while (p < k && (path_tek = bfs_k_path(map, cant_go)) && path_not_in(path_tek, cant_go) == 1)
	{
		ft_list_add_back_down_next(&path_down, path_tek);
		tmp->down->content = ft_list_len_i(path_tek);
		//ft_list_add_back_i(&cant_go, path_tek);/* дополним список по которому нельзя ходить */
		ft_list_add_back_i(&cant_go, path_tek);
		ft_free_list_i(&path_tek);
		//ft_fr
		path_tek = NULL;
		ft_list_add_back_down(&path_down, ft_list_new_down(-10));//path_down->down = (t_list_down*)malloc(sizeof(t_list_down));
		tmp = tmp->down;
		p++;
	}
	ft_free_list_i(&cant_go);
	return (path_down);
}

