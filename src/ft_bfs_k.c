#include "lem_in.h"

//есть ли клмната в списке?
int find_room(t_list_i *room, int num)
{
	while (room)
	{
		if (room->content == num)
			return (1);
		room = room->next;
	}
	return (0);
}

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
	//ссылка на начало, что б вернуть
	start = path;

	while (path && path->content != 0)// пока не придем в комнату старта ищем путь
	{
		f = 1;
		//найдем dest с весом dist[path->content] - 1) и если из него есть ссылка в насБ добавим путь
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
						ft_list_add_back_i(&path, ft_list_new_i(tmp_n));
						f = 0;
						break ;
					}
					tmp_i = tmp_i->next;
				}
			}
			i++;
		}
		path = path->next;//переход к комнате, которую добавили
	}

	//ft_list_revers(&start);
	path = start;
	while(path)
	{
		if (path->content > map->c_room)
			path->content -= map->c_room;
		path = path->next;
	}
	ft_list_revers(&start);
	free(dist);
	return (start);
}

//находит к-ый путь, не ходя по списку использованных путей
t_list_i 		*bfs_k_path(t_map *map, t_list_i *cant_go)
{
	int			i;
	int 		*dist; //массив интов - расстояние от старта
	t_list_i 	*order;
	t_list_i *all_order;
	t_list_down *tmp;
	t_list_i 	*tmp_i; //я поэтому из ft_list_i_head хотела возвращать сразу t_list_i, что б 2 раза одно и тоже не писать
	int 		len;
	int f;

	len = 0;
	dist = (int*)malloc(sizeof(int) * (2*map->c_room + 1));
	i = 0;
	while (i <= 2*map->c_room)
		dist[i++] = 2*map->c_room + 1;
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
	dist[0] = 0;
	f = 1;
	// будем продолжать пока есть очередь или пока не нашли кратчайший путь (нашли комнатц энд)
	while (order && !len && (tmp = ft_list_i_head(order->content, map->link_new)) && f)
	{
		f = 1;
		//возвращаем ссылку на комнату
//		tmp = ft_list_i_head(order->content, map->link_new);
		tmp_i = tmp->next;//надо пропустить себя же ! ЗАПИСЬ НИЖЕ РАБОТАЕТ -2строки =)
		//tmp_i = ft_list_i_head(order->content, map->link)->next;
		//пока есть комнаты(tmp), связанные с комнатой в очереди
		//перезаписываем расстояние, если до этого оно было больше
		while (tmp_i && len == 0 && f)
		{
			//если в комнате, которую мы проверяем растояние от начала больше, чем от соседа которого мы можем дотянуться
			if (dist[tmp_i->content] > dist[order->content] + 1 && (tmp_i->content != order->content))
			{

				dist[tmp_i->content] = dist[order->content] + 1;
//				if (tmp_i->content > map->c_room)
//					dist[tmp_i->content - map->c_room] = dist[order->content] + 1;
			}
			if (tmp_i->content == map->c_room)//нашли короткий путь, если пришли в последнюю комнату
			{
				len = dist[tmp_i->content]; // надо выходить из цикла while(order && !len)
				f = 0;
				//ft_printf("bfs_k_path /// %d %d %d %d %d = \n",len, tmp_i->content, dist[tmp_i->content], dist[order->content], order->content);
			}
			//для каждого узла добавляем очередь соседей если нет в запрещеном списке
			else if (dist[tmp_i->content] != -1 && find_room(order ,tmp_i->content) == 0)
			{
				ft_list_add_back_i_if_not(&order, tmp_i->content, all_order);//ft_list_add_back_i(&order, ft_list_new_i(tmp_i->content));
				ft_list_add_back_i(&all_order, ft_list_new_i(tmp_i->content));
			}
			tmp_i = tmp_i->next;
		}
		//free(tmp);
		order = order->next;
	}
	if (len == 0) //если длина осталась нулевой
	{
		free(order);//знаю что не чищу
		free (dist);
		ft_printf("no path\n");
		return (NULL);
	}
	else //найдем коротуий путь (реверс) и вернем 1 оттуда
	{
	//	printf("oooo");
//		while (path_down && path_down->down && path_down->down->content != -10)
//			path_down = path_down->down;
//		path_down->down->content = len;
		return (ft_path_k(map, dist));
	}
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
	while (p < k && (path_tek = bfs_k_path(map, cant_go)))
	{
		//самого себя можно передаь для записи длины?
		//pr_list(path_tek);

		//ft_list_add_back_down(&path_down, ft_list_new_pointer_down(path_tek));
		ft_list_add_back_down_next(&path_down, path_tek);
		//ft_list_add_back_i(&tmp->down->next, path_tek);//path_down->down->next = path_tek;
		//ft_print_all_path(path_down);
		tmp->down->content = ft_list_len_i(path_tek);
		//ft_list_add_back_down(&path_down,)
		//дополним список по которому нельзя ходить
		ft_list_add_back_i(&cant_go, path_tek);
		//ft_printf("!!!now\n");
		//ft_print_all_path(path_down);
		//ft_printf("1 = %p , %p \n", cant_go, path_down->down->down);

		path_tek = NULL;
		//ft_printf("end_now!\n");
		//ft_list_add_back_i(&cant_go , path_tek);

		//ft_printf("2 = %p , %p \n", cant_go, path_down->down->down);
		//ft_print_all_path(path_down);
//		while(path_tek)
//		{
//			///printf("ppp = %d - ",path_tek->content);
//			path_tek = path_tek->next;
//		}
//		printf("\n\n");
		ft_list_add_back_down(&path_down, ft_list_new_down(-10));//path_down->down = (t_list_down*)malloc(sizeof(t_list_down));
		//path_down->down->next = NULL;
		tmp = tmp->down;
		p++;
	}

	return (path_down);
}

