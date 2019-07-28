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
		while (list->next)
		{
			tmp = list;
			list = list->next;
		}
		list->next = ft_list_new_path(num_ant, name, tmp);
	}
	else
	{
		list = ft_list_new_path(num_ant, name, NULL);
		*head = list;
	}
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
	int c_path;
	int *d;
	int i;
	int k;
	int 	c_ant;
	int 	num_ant;
	int 	max_d;
	t_list_down *tmp;
	t_list_path *tmp_path;
	t_list_path *path_n;
	t_list_i	*tmp_i;

	c_path = ft_list_len_down(map->two_path) - 1; // тк последняя -10
	d = (int*)malloc(sizeof(int) * (c_path));
	tmp_path = (t_list_path*)malloc(sizeof(t_list_path) * (c_path));
	tmp = map->two_path->down;
	i = 0;
	while (i < c_path)
	{
		d[i] = tmp->content;
		k = 0;
		tmp_i = tmp->next;

		while (k < d[i])
		{
			printf("dd = %d\n",tmp_i->content);
			printf("name = %s \n", ft_name_room(map->rooms, tmp_i->content));
			path_n = tmp_path + i;
			ft_list_add_back_path(&path_n, 0, ft_name_room(map->rooms, tmp_i->content) );
			printf("name = %s, num = %d, %p, p_p %p\n", path_n->next->name_room, tmp_path[i].next->num_ant, tmp_path[i].next->next, tmp_path[i].next->prev);

			tmp_i = tmp_i->next;
			k++;
		}
		tmp = tmp->down;
		//printf("len = %d  \n ", d[i]);
		i++;
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


}