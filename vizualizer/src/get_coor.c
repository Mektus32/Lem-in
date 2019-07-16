/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:39:11 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/16 15:39:12 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

int 	ft_get_x_room(t_room *room, char *name)
{
	t_room	*list;

	list = room;
	while (list)
	{
		if (!ft_strcmp(list->name, name))
			return (list->x);
		list = list->down;
	}
	return (-100);
}

int 	ft_get_y_room(t_room *room, char *name)
{
	t_room *list;

	list = room;
	while (list)
	{
		if (!ft_strcmp(list->name, name))
			return (list->y);
		list = list->down;
	}
	return (-100);
}

int 	ft_get_x_room_cont(t_room *room, int cont)
{
	t_room	*list;

	list = room;
	while (list)
	{
		if (list->cont == cont)
			return (list->x);
		list = list->down;
	}
	return (-100);
}

int 	ft_get_y_room_cont(t_room *room, int cont)
{
	t_room	*list;

	list = room;
	while (list)
	{
		if (list->cont == cont)
			return (list->y);
		list = list->down;
	}
	return (-100);
}