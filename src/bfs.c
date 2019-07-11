#include "lem_in.h"
//0 если не найдкм ни одного пути

int ft_bfs(t_map *map)
{
	t_map *kek;

	kek = map;
//	int i;
//	int *dist;
//	int len;
//	int k;
//	t_list_i *order;
//	t_list_i *start;
//	t_list_i *tmp;
//	len = 0;
//	i = 0;
//	//массив интов
//	dist = (int*)malloc(sizeof(int) * map->c_room);
//	while (i <= map->c_room)
//		dist[i++] = 100;
//	order = ft_lstnew_i(0);
//	i = 0;
//	dist[0] = 0;
//	while (order && len == 0)
//	{
//		tmp = ft_list_i_head(i, &map->link);//map->matr[i];
//		//tmp = tmp->next;//надо пропустить себя же или удалить себя когда строим список смежости
//		while (tmp)
//		{
//			if (dist[tmp->content] > dist[i] + 1)
//				dist[tmp->content] = dist[i] + 1;
//			if (tmp->content == map->c_room)//нашли короткий путь
//				len = dist[tmp->content];
//
//			//для каждого узла добавляем очередь соседей
//			ft_lstaddback_i(&order, ft_lstnew_i(tmp->content));
//			tmp = tmp->next;
//		}
//		printf("o_c = %d\n", order->content);
//		order = order->next;
//		i = order->content;
//	}
//	free(order);
//	tmp = ft_list_i_head(i, &map->link);
//	tmp = tmp->next;//первая связанная комната
//	//новая очередб как путь (обратный путь)
//	order = ft_lstnew_i(map->c_room);
//	//ссылка на начало, что б вернуть
//	start = order;
//	//если предыдущих ячеек несколько нам не важно, тк путь все = будет кротчайший
//	while (order && order->content != 0)
//	{
//		// И ВОТ ТУТ
//		tmp = map->matr[order->content];
//		tmp = tmp->next;
//		while (tmp)
//		{
//			if (dist[tmp->content] == (dist[order->content] - 1))
//			{
//				printf("aaa\n");
//				ft_lstaddback_i(&order, ft_lstnew_i(tmp->content));
//				break ;
//			}
//			tmp = tmp->next;
//		}
//		order = order->next;
//		printf("o_c1 = %d\n", order->content);
//	}
//	map->sh = start;
	return(0);
}

