/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avalid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 21:05:57 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/16 21:06:00 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				make_ant(t_map *map)
{
	char	*line;
	int		i;

	line = NULL;
	line = ft_check_cmd(&map->fd);
	if (line && !(ft_strequ(line, "##start") || ft_strequ(line, "##end")))
	{
		i = 0;
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if ((int)ft_strlen(line) == i)
		{
			map->c_ant = ft_atoi(line);
			ft_str_print_del(&line);
			if (map->c_ant == 0 || map->c_ant >= 2147483647)
				return (is_not_valid("ant_count err\n"));
			return (1);
		}
		ft_str_print_del(&line);
		return (is_not_valid("no find ant_count\n"));
	}
	return (is_not_valid("no find ant_count\n"));
}

static int		is_elem(char *line)
{
	int		i;

	if (!line || line[0] == '\0')
		return (0);
	if (line[0] == 'L' && ft_count_words(line) != 3)
		return (0);
	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		return (0);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		return (0);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (i == (int)ft_strlen(line))
		return (1);
	return (0);
}

/*
**Пока есть гнл возможны случаи:
**1. нам дана комната
**2. нам дано старт-энд положение комнаты
**3. комент #
**4. cсылка
**комнаты могут следовать в любом порядке. так что выхода кроме как запомнить
**первую и последнюю я не нашла.
**новую комнату когда находим ставим её в конец,
**последнюю комнату ставим в конец, когда комнаты закончались и начались ссылки
**комнату старт ставим в начало
**если нет или первой или последней комнаты возвращаем 0
*/

static int		start_room(t_map *map, t_valid *val_id, char *line)
{
	val_id->start = val_id->end != 1 ? 1 : 4;
	ft_str_print_del(&line);
	line = ft_check_cmd(&map->fd);
	if (val_id->start == 1 && line && is_elem(line))
	{
		ft_list_add_room(&map->rooms, ft_create_ele(line, 0));
		val_id->start = 2;
	}
	else
		return (is_not_valid("start room_error"));
	return (0);
}

static t_room	*end_room(t_map *map, t_valid *val_id, char *line)
{
	t_room	*last_room;

	last_room = NULL;
	val_id->end = val_id->start != 1 ? 1 : 4;
	ft_str_print_del(&line);
	line = ft_check_cmd(&map->fd);
	if (val_id->end == 1 && line && is_elem(line))
	{
		last_room = ft_create_ele(line, -1);
		val_id->end = 2;
	}
	else
		is_not_valid("end room_error");
	return (last_room);
}

int				check_room(t_map *map, t_room *last_room)
{
	char	*line;
	t_valid *val_id;

	val_id = ft_create_val();
	while ((line = ft_check_cmd(&map->fd)))
	{
		if (val_id->start == 0 && ft_strequ(line, "##start"))
			start_room(map, val_id, line);
		else if (val_id->end == 0 && ft_strequ(line, "##end"))
			last_room = end_room(map, val_id, line);
		else if (last_room && ft_strchr(line, '-') && !ft_strchr(line, ' '))
		{
			last_room->number = val_id->tek_num;
			ft_push_back_room(&map->rooms, last_room);
			map->c_r = val_id->tek_num;
			return (created_links(line, map, val_id));
		}
		else if (is_elem(line))
			ft_push_back_room(&map->rooms,
					ft_create_ele(line, val_id->tek_num++));
		else
			return (is_not_valid("room_error"));
	}
	return (0);
}
