#include "lem_in.h"

int		ft_count_ant(t_list_path *path)
{
		int			j;
		t_list_path	*list;

		if (!path)
			return (1);
		j = 0;
		list = path->next;
		while (list)
		{
			if (list->num_ant != 0)
				j++;
			list = list->next;
		}
		return (j);

}

void	ft_move_ant_in_path(t_list_path *path)
{
	t_list_path	*list;

	if (!path)
		return ;
	list = path;
	while (list->next)
		list = list->next;
	while (list->prev)
	{
		list->num_ant = 0;
		list->num_ant = list->prev->num_ant;
		if (list->prev->num_ant != 0)
			ft_printf("L%d-%s ", list->prev->num_ant, list->name_room);
//		if (list->prev && list->prev->num_ant != 0)
//			ft_printf(" ");
		list->prev->num_ant = 0;
		list = list->prev;

	}
}

void	ft_pars_ant(t_map *map, t_list_path *paths, int count)
{
	int 	i;
	int 	j;

	i = 1;
	while (i < map->c_ant + 1)
	{
		j = -1;
		while (++j < count)
		{

			if (paths[j].num_ant > 0)
			{
				paths[j].num_ant--;
				paths[j].next->num_ant = i;
				i++;
			}
			ft_move_ant_in_path(paths[j].next);
		}
		ft_printf("\n");
	}
	j = 1;
	while (j)
	{
		j = 0;
		i = -1;
		while (++i < count)
		{

			j += ft_count_ant(&paths[i]);
			ft_move_ant_in_path(&paths[i]);
			//if (i == count)

		}
		if (j != 0 && i == count)
			ft_printf("\n");
		//if (i == count - 1)

	}
}


void ant_in_room(t_map *map)
{
	int c_path;//кол-во путей
	int *d;//массив длины путей
	int i;
	int k;
	int f;
	int 	c_ant;

	t_list_down *tmp;
	t_list_path *tmp_path;
	t_list_path *path_n;
	t_list_i	*tmp_i;
	char *name_2;

	c_path = ft_list_len_down(map->two_path); // тк последняя -10
	c_path = (c_path == 1 ? c_path : c_path - 1);
	d = (int*)malloc(sizeof(int) * (c_path));
	tmp_path = path_n_mass(c_path);
	tmp = map->two_path->down;
	i = 0;
	// для каждого итого пути
	while (i < c_path)
	{
		d[i] = tmp->content;//длина каждого пути
		k = 0;
		tmp_i = tmp->next;
		// для каждой комнаты в итом пути запишем связи на след и пред комнату
		// в каждой комнате храним номер текущего муравья (0 изначально)
		while (k < d[i])
		{
			path_n = NULL;
			path_n = tmp_path + i;
			name_2 = (ft_name_room(map->rooms, tmp_i->content));
			ft_list_add_back_path(&path_n, 0, name_2);//всем комнатам раздадим 0 муравьев
			//tmp_path[i].num_ant = 0;// а то вдркг мусор лежать будет - кол-во муравьевБ которое пойдет по пути
			tmp_i = tmp_i->next;
			k++;
		}
		tmp = tmp->down;
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
	free(d);
	c_path = (tmp_path[i - 1].num_ant == 0 ? c_path - 1 : c_path);
	map->c_path = c_path;
	// начинаем расставлять муравьев в комнатам по порядку
	// пока есть пути и кол-во муравьев в пути не 0 бернм мкравья и переносим его в след комнату, если комната не последняя
	ft_pars_ant(map, tmp_path, c_path);
	free_tmp_path(&tmp_path, c_path);
}

