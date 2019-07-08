#include "lem_in.h"
//-1 если не найдкм ни одного пути


t_list_i	*ft_lstnew_i(int content)
{
	t_list_i	*list;

	list = NULL;
	list = (t_list_i*)malloc(sizeof(t_list_i));
	if (!list)
		return (NULL);
	if (!content)
	{
		list->content = 0;
	}
	else
	{
		// list->content = malloc(sizeof(int));
		// if (!list->content)
		// 	return (NULL);
		list->content = content;
	}
	list->next = NULL;
	return (list);
}

void	ft_lstaddback_i(t_list_i **alst, t_list_i *new)
{
	t_list_i *list;

	if (!alst)
		return ;
	list = *alst;
	if (*alst)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}



int ft_bfs(t_map *map)
{
	int i;
	//int pr_end;
	int *dist;
	int len;
	int k;
	//t_room *room;
	t_list_i *order;
	t_list_i *start;
	t_list_i *tmp;
	len = 0;
	i = 0;
	//массив интов
	dist = (int*)malloc(sizeof(int) * map->c_room);
	while (i <= map->c_room)
		dist[i++] = 100;
	order = ft_lstnew_i(0);

	i = 0;
	dist[0] = 0;
	while (order && len == 0)
	{
		tmp = map->matr[i];
		//ВОТ ТУТ НАДО ДЕЛАТЬ ЛИШНЕЕ ДЕЙСТВИЕ ПО ПЕРЕХОДУ К СЛЕД СВЯЗИ, ТК ПЕРВАЯ КОМНАТА ССЫЛАЕТСЯ НА СЕБЯ 
		tmp = tmp->next;//надо пропустить себя же или удалить себя когда строим список смежости
		while (tmp)
		{
			if (dist[tmp->content] > dist[i] + 1)
				dist[tmp->content] = dist[i] + 1;
			if (tmp->content == map->c_room)//нашли короткий путь
				{
					k = 0;
					while (k <= map->c_room)
						printf("%d ", dist[k++]); // есть даже не помеченные вершины
					len = dist[tmp->content];
					//return (dist[tmp->content]);
				}
			//для каждого узла добавляем очередь соседей
			ft_lstaddback_i(&order, ft_lstnew_i(tmp->content));
			tmp = tmp->next;

		}

		printf("o_c = %d\n", order->content);
		order = order->next;
		i = order->content;
	}
	free(order);
	
	//востановление кратчайшего пути 
	tmp = map->matr[map->c_room];
	// И ВОТ ТУТ
	tmp = tmp->next;//первая связанная комната
	//новая очередб как путь (обратный путь)
	order = ft_lstnew_i(map->c_room);
	//ссылка на начало, что б вернуть
	start = order;
	//если предыдущих ячеек несколько нам не важно, тк путь все = будет кротчайший
	while (order && order->content != 0)
	{
		// И ВОТ ТУТ
		tmp = map->matr[order->content];
		tmp = tmp->next;
		while (tmp)
		{
			if (dist[tmp->content] == (dist[order->content] - 1))
			{
				printf("aaa\n");
				ft_lstaddback_i(&order, ft_lstnew_i(tmp->content));
				break ;
			}
			tmp = tmp->next;
		}
		order = order->next;
		printf("o_c1 = %d\n", order->content);
	}
	//ft_lstaddback_i(&start, ft_lstnew_i(0));
	map->sh = start;


	return(len);
}

