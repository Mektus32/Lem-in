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

	//обратный путь начинается с последней комнаты
	path = ft_lstnew_i(map->c_room);
	//ссылка на начало, что б вернуть
	start = path;
	while (path->content != 0)// пока не придем в комнату старта ищем путь
	{
		tmp_i = (ft_list_i_head(path->content, map->link_new))->next;
		while (tmp_i)// ищем комнату с весом на 1 меньше, чем текущая
		{//если предыдущих ячеек несколько нам не важно, тк путь все = будет кротчайший
			if (dist[tmp_i->content] == (dist[path->content] - 1))
			{
				ft_lstaddback_i(&path, ft_lstnew_i(tmp_i->content));
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

//находит к-ый путь, не ходя по списку использованных путей
t_list_i 		*bfs_k_path(t_map *map, t_list_i *cant_go, t_list_down *path_down)
{
	int			i;
	int 		*dist; //массив интов - расстояние от старта
	t_list_i 	*order;
	t_list_down *tmp;
	t_list_i 	*tmp_i; //я поэтому из ft_list_i_head хотела возвращать сразу t_list_i, что б 2 раза одно и тоже не писать
	int 		len;

	len = 0;
	dist = (int*)malloc(sizeof(int) * (map->c_room + 1));
	i = 0;
	while (i <= map->c_room)
		dist[i++] = map->c_room + 1;
	i = 0;
	//есди комната в списке занятых, дам ей вес -1, что б больше не ходить по ней
	while (i <= map->c_room)
	{
		if (find_room(cant_go, i))
			dist[i] = -1;
	}

	//начинаем очередь в очередь добавляем все вершины, которые встретелись на пути
	order = ft_lstnew_i(0);
	dist[0] = 0;
	// будем продолжать пока есть очередь или пока не нашли кратчайший путь (нашли комнатц энд)
	while (order && !len)
	{
		//возвращаем ссылку на комнату
		tmp = ft_list_i_head(order->content, map->link_new);
		tmp_i = tmp->next;//надо пропустить себя же ! ЗАПИСЬ НИЖЕ РАБОТАЕТ -2строки =)
		//tmp_i = ft_list_i_head(order->content, map->link)->next;
		//пока есть комнаты(tmp), связанные с комнатой в очереди
		//перезаписываем расстояние, если до этого оно было больше
		while (tmp_i && map->two_path->down->content == 0)
		{
			//если в комнате, которую мы проверяем растояние от начала больше, чем от соседа которого мы можем дотянуться
			if (dist[tmp_i->content] > dist[order->content] + 1 && (tmp_i->content != order->content))
				dist[tmp_i->content] = dist[order->content] + 1;
			if (tmp_i->content == map->c_room)//нашли короткий путь, если пришли в последнюю комнату
				len = dist[tmp_i->content]; // надо выходить из цикла while(order && !len)
			//для каждого узла добавляем очередь соседей если нет в запрещеном списке
			else if (dist[tmp_i->content] != -1)
				ft_lstaddback_i(&order, ft_lstnew_i(tmp_i->content));
			tmp_i = tmp_i->next;
		}
		//free(tmp);
		order = order->next;
	}
	if (len == 0) //если длина осталась нулевой
	{
		free(order);//знаю что не чищу
		free (dist);
		printf("no path\n");
		return (NULL);
	}
	else //найдем коротуий путь (реверс) и вернем 1 оттуда
	{
		path_down->down->content = len;
		return (ft_path_k(map, dist));
	}
}


//поиск к кратчайших путей
t_list_down		*ft_bfs_k(t_map *map, int k)
{
	t_list_i	*path_tek;
	t_list_down *path_down;
	t_list_i	*cant_go;//список по которому нельзя ходить
	int p;

	p = 0;
	path_down = (t_list_down*)malloc(sizeof(t_list_down));
	path_down->down = (t_list_down*)malloc(sizeof(t_list_down));
	path_down->down->next = NULL;
	cant_go = (t_list_i*)malloc(sizeof(t_list_i));

	while (path_tek = bfs_k_path(map, cant_go, path_down) && p < k)
	{
		//переходимк след пути6 пока они есть
//		while(path_down->down->next)
//			path_down = path_down->down;
		//самого себя можно передаь для записи длины?
		path_down->down->next = path_tek;
		//дополним список по которому нельзя ходить
		ft_lstaddback_i(cant_go , path_tek);
		path_down->down = (t_list_down*)malloc(sizeof(t_list_down));
		path_down->down->next = NULL;
		path_down = path_down->down;
	}
	return (path_down);
}

