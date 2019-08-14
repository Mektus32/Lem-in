/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aant_in_room_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:02:00 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 20:02:40 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_count_ant(t_list_path *path)
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

static int		sum_ant(t_list_path **path_a, int c_path)
{
	int			ant;
	int			i;
	t_list_path *tmp_i;

	ant = 0;
	i = 0;
	while (i < c_path)
	{
		tmp_i = *path_a + i;
		tmp_i = tmp_i->next;
		while (tmp_i)
		{
			ant += tmp_i->num_ant;
			tmp_i = tmp_i->next;
		}
		i++;
	}
	return (ant);
}

void			ft_move_ant_in_path(t_list_path **path_a)
{
	t_list_path	*list;

	if (!path_a)
		return ;
	list = *path_a;
	while (list->next)
		list = list->next;
	while (list->prev)
	{
		list->num_ant = 0;
		list->num_ant = list->prev->num_ant;
		if (list->prev->num_ant != 0)
		{
			ft_printf("L%d-%s ", list->prev->num_ant, list->name_room);
		}
		list->prev->num_ant = 0;
		list = list->prev;
	}
}

int				ft_len_path(t_list_path **path_a, int j)
{
	int			len;
	t_list_path	*tmp;

	len = 0;
	tmp = *path_a + j;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len - 1);
}

void			ft_pars_ant(t_map *map, t_list_path **path_a)
{
	int			i;
	int			j;
	t_list_path	*paths;
	t_list_path	*paths_k;

	if (!path_a || !*path_a)
		return ;
	paths = *path_a;
	i = 1;
	while (i < map->c_ant + 1)
	{
		j = -1;
		while (++j < map->c_path)
		{
			if (paths[j].num_ant > 0)
			{
				paths[j].num_ant--;
				paths[j].next->num_ant = i;
				i++;
			}
			ft_move_ant_in_path(&paths[j].next);
		}
		if (ft_len_path(&paths, j - 1) != 2)
			ft_printf("\n");
	}
	j = 1;
	while (j)
	{
		j = 0;
		i = -1;
		while (++i < map->c_path)
		{
			j += ft_count_ant(&paths[i]);
			paths_k = paths + i;
			ft_move_ant_in_path(&paths_k);
		}
		if (j != 0 && i == map->c_path && sum_ant(&paths, map->c_path) != 0)
		{
			ft_printf("\n");
		}
	}
}
