/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aant_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:21:41 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 20:21:54 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** заполнение массива  путей муравьями (исходным колличеством)
*/

static void	ant_in_path(int *d, t_list_path *tmp_path, t_map *map)
{
	int		c_ant;
	int		i;

	c_ant = map->c_ant;
	i = 0;
	while (i < map->c_path)
	{
		while ((tmp_path[i].num_ant + d[i] < (map->two_path->content +
		map->c_path)) && c_ant)
		{
			if (c_ant)
			{
				tmp_path[i].num_ant += 1;
				c_ant--;
			}
		}
		i++;
	}
}

/*
** d[i]длина каждого пути
** path_add_i - добавляет в массив путей текущий
** надо посчитать количество муравье которое отправиться в каждую комнату
** tmp_path[i].num_ant
** начинаем расставлять муравьев в комнатам по порядку
** пока есть пути и кол-во муравьев в пути не 0 бернм мкравья и переносим его в
** след комнату, если комната не последняя
*/

void		ant_in_room(t_map *map) {
	int *d;
	int i;
	t_list_down *tmp;
	t_list_path *tmp_path;

	map->c_path = ft_list_len_down(map->two_path);
	map->c_path = (map->c_path == 1 ? map->c_path : map->c_path - 1);
	d = (int *) malloc(sizeof(int) * (map->c_path));
	tmp_path = path_n_mass(map->c_path);
	tmp = map->two_path->down;
	i = -1;
	while (++i < map->c_path && tmp) {
		d[i] = tmp->content;
		path_add_i(tmp_path + i, d[i], map, tmp->next);
		tmp = tmp->down;
	}
	ant_in_path(d, tmp_path, map);
	free(d);
	map->c_path = (tmp_path[i - 1].num_ant) == 0 ?
				  map->c_path - 1 : map->c_path;
	ft_pars_ant(map, &tmp_path);
	free_tmp_path(&tmp_path, map->c_path);
}

