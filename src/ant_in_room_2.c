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

int				ft_count_ant(t_list_path *path)
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

int				sum_ant(t_list_path **path_a, int c_path)
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
