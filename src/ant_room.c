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
	//free(line);
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
		while (list && list->next)
		{
			tmp = list;
			list = list->next;
		}
		if (tmp && tmp->next)
			list->next = ft_list_new_path(num_ant, name, tmp->next);
		else
			list->next = ft_list_new_path(num_ant, name, NULL);

		//(*head)->next = ft_list_new_path(num_ant, name, tmp);
		//printf("name[%s]\n", list->next->name_room);
	}
	else
	{
		list = ft_list_new_path(num_ant, name, NULL);
		*head = list;
	}
	(*head)->next->next ? printf("name[%s]\n", (*head)->next->next->name_room) : 0;
	return (list);
}

//t_list_path	*ft_list_new_path(int num_ant, char *name)
//{
//	t_list_path	*list;
//
//
//
//
//void	ft_list_add_back_path(t_list_path **lst_a, t_list_path *new)
//{
//	t_list_path *list;
//	t_list_path	*tmp_prev;
//
//	if (!(lst_a))
//		return ;
//	list = *lst_a;
//	if (*lst_a)
//	{
//		tmp_prev = list;
//		while (list->next)
//		{
//			tmp_prev = list;
//			list = list->next;
//		}
//		list->next = new;
//		list->prev = tmp_prev;
//	}
//	else
//		*lst_a = new;
//}


void ant_in_room(t_map *map)
{
	int c_path;//кол-во путей
	int *d;//массив длины путей
	int i;
	int k;
	int f;
	int 	c_ant;
	int 	num_ant;
	int 	max_d;
	int len_max;
	t_list_down *tmp;
	t_list_path *tmp_path;
	t_list_path *path_n;
	t_list_path *path_n_tmp;
	t_list_i	*tmp_i;
	char *name_2;

	c_path = ft_list_len_down(map->two_path) - 1; // тк последняя -10
	d = (int*)malloc(sizeof(int) * (c_path));
	tmp_path = (t_list_path*)malloc(sizeof(t_list_path) * (c_path));
	tmp = map->two_path->down;
	i = 0;
	// для каждого итого пути
	while (i < c_path)
	{
		d[i] = tmp->content;
		k = 0;
		tmp_i = tmp->next;
		// для каждой комнаты в итом пути запишем связи на след и пред комнату
		// в каждой комнате храним номер текущего муравья (0 изначально)
		while (k < d[i])
		{
//			printf("dd = %d\n",tmp_i->content);
		//	printf("name = %s ,\n", ft_name_room(map->rooms, tmp_i->content));
			path_n = tmp_path + i;
			name_2 = (ft_name_room(map->rooms, tmp_i->content));
		//	printf("name_2 = %s ,\n", name_2);
			ft_list_add_back_path(&path_n, 0, name_2);
			tmp_path[i].num_ant = 0;// а то вдркг мусор лежать будет - кол-во муравьевБ которое пойдет по пути
			//tmp_path[i].next->name_room = name_2;
		//	printf("name = %s, num = %d, %p, p_p %p\n", tmp_path[i].next->name_room, tmp_path[i].next->num_ant, tmp_path[i].next->next, tmp_path[i].next->prev);

			tmp_i = tmp_i->next;
			k++;
		}
		tmp = tmp->down;
		//printf("len = %d  \n ", d[i]);
		i++;
	}
	// надо посчитать количество муравье которое отправиться в каждую комнату tmp_path[i].num_ant
	c_ant = map ->c_ant;
	i = 0;
	while (i < c_path)
	{
		f = 0;

		while ((tmp_path[i].num_ant + d[i]  < (map->two_path->content)) && c_ant)//tmp_path[i].num_ant <= len_max &&
		{
			if (c_ant)
			{
				tmp_path[i].num_ant += 1;
				c_ant--;
				f++;
			}
		}
		i++;
	}
	// начинаем расставлять муравьев в комнатам по порядку
	// пока есть пути и кол-во муравьев в пути не 0 бернм мкравья и переносим его в след комнату, если комната не последняя
	i = 0;
	while (i < c_path)
	{
		printf("i = %d, c_a = %d\n", i, tmp_path[i].num_ant);
		i++;
	}
	i = 0;
	c_ant = map ->c_ant;
	k = 1;
	// для каждого пути
	while (i < c_path)
	{
		//в комнату в которой встречаем первый 0 передвигаем муравья
		path_n = tmp_path + i;
		while (path_n->next->num_ant != 0)
			path_n = path_n->next;
		path_n = path_n->next;
		if (tmp_path[i].num_ant && k <= c_ant)// берем муравья и помещаем его в комнату
		{
			path_n->num_ant = k++;
			tmp_path[i].num_ant -= 1;
		}
		else // берем муравья из пред комнаты
		{
			path_n->num_ant = path_n->prev->num_ant;
			path_n->prev->num_ant = 0;
		}
		//пока сзади не кончаются муравьи переставляем их местами
		path_n_tmp = path_n->prev;
		while (path_n_tmp && path_n_tmp->prev && path_n_tmp->prev->num_ant != 0)
		{
			path_n->prev->num_ant = path_n_tmp->prev->num_ant;
			path_n_tmp->prev->num_ant = 0;
			path_n_tmp = path_n_tmp->prev;
		}
		// печатаем все комнаты где не 0 (начинаем с конца)
		path_n = tmp_path + i;
		while (path_n->num_ant != 0)
			path_n = path_n->next;
		while (path_n && path_n->num_ant)
		{
			printf("L%d-%s ",path_n->num_ant, path_n->name_room);
			path_n = path_n->prev;
		}
		i++;
		printf("\n");


	}




	}




	// пока время каждого пути не достигнет максимального пути будем отправлять муравьев по всем путям
	// и остаток от деления мурявьев на уол-во путей будет превышать количестко путей
//	i = 0;
//	while (i < c_path)
//	{
//		ft_printf("%d ", i);
//		*path_n = tmp_path[i];
//		while (path_n)
//		{
//			printf("mane = %s, num = %d\n", path_n->name_room, path_n->num_ant, path_n->next, path_n->prev);
//			path_n = path_n->next;
//		}
//		i++;
//	}

//	c_ant = map->c_ant;
//	max_d = ft_max_mass(d);
//	num_ant = 1;
//	while (num_ant <= c_ant)
//	{
//		i = 0;
//		*path_n = tmp_path[i];
//		//пока не кончатся муравьи
//		while (num_ant < c_path)
//		{
//			while (path_n->num_ant != 0)
//			{
//				path_n = path_n->next;
//			}
//
//
//		}
//	}


