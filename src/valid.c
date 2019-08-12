/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:05:39 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/14 15:05:46 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
// заполним начальнуб струкруру map
// проверим на валидность первую строку (кол-во муравьев)
// ? если муравьев 0 кидать ошибку?
int		make_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	line = NULL;
	map->fd = fd;
	map->len_sh = 0;
	map->c_room = 0;
	map->rooms = NULL;

	line = ft_check_cmd(map->fd);
	if (line && !(ft_strequ(line, "##start") || ft_strequ(line, "##end")))
	{
		i = 0;
		while (ft_isdigit(line[i]))
			i++;
		if ((int)ft_strlen(line) == i)
		{
			map->c_ant = ft_atoi(line);
			ft_str_print_del(&line);
			if (map->c_ant == 0 || map->c_ant >= 2147483647)
				return (0);
			return (1);
		}
		ft_str_print_del(&line);
		return (0);
	}
	return (0);
}

int is_elem(char *line)
{
	int		i;

	if (!line || line[0] == '\0')
		return (0);
	i = 0;
	//это имя
	if (line[0] == 'L' && ft_count_words(line) != 3)
		return (0);
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	i++;
	if (!ft_isdigit(line[i]))
		return (0);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	i++;
	if (!ft_isdigit(line[i]))
		return (0);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

/*
Пока есть гнл возможны случаи:
1. нам дана комната
2. нам дано старт-энд положение комнаты
3. комент #
4. cсылка

комнаты могут следовать в любом порядке. так что выхода кроме как запомнить
первую и последнюю я не нашла.
новую комнату когда находим ставим её в конец,
последнюю комнату ставим в конец, когда комнаты закончались и начались ссылки
комнату старт ставим в начало

если нет или первой или последней комнаты возвращаем 0
*/

int	check_room(t_map *map)
{
	char	*line;
	int		number;
	t_room	*last_room;

	number = 1;
	last_room = NULL;
	line = ft_check_cmd(map->fd);
	while (line)
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		{
			if (ft_strequ(line, "##start") == 1)//и еще не было перволй комнаты
			{

				ft_str_print_del(&line);
				line = ft_check_cmd(map->fd);
				if (line != NULL && is_elem(line) && ((map->rooms && map->rooms->number != 0) || map->rooms == NULL) )
					ft_list_add_room(&map->rooms, ft_create_ele(line, 0));
				else {
					ft_str_print_del(&line);
					return (0);
				}
			}
			else if (last_room == NULL)
			{
					ft_str_print_del(&line);
					line = ft_check_cmd(map->fd);
				if (line != NULL && is_elem(line))
					last_room = ft_create_ele(line, -1);
				else
				{
					ft_str_print_del(&line);
					return (0);
				}
			}
			else
			{
				ft_str_print_del(&line);
				return (0);
			}
			line = ft_check_cmd(map->fd);
		}
		else if (ft_strchr(line, '-') && ft_strchr(line, ' ') == NULL)
		{
			if (last_room)
			{
				last_room->number = number;
				ft_push_back_room(&map->rooms, last_room);
			}
			else {
				ft_str_print_del(&line);
				return (0);
			}
			map->c_room = number;
			return (created_links(line, map));
		}
		else if (is_elem(line))
		{
			ft_push_back_room(&map->rooms, ft_create_ele(line, number));
			number++;
			line = ft_check_cmd(map->fd);
		}
		else
		{
			ft_str_print_del(&line);
			return (0);
		}
	}
	ft_str_print_del(&line);
	return (0);
}

/*
ф. вызывается для каждой входной строки, где есть - и нет ' '
заполняет ссылки в две стороны
если не нашли одну из комнат - возвращает 0
 start = map->rooms; - //находим комнату из строки до '-' во всем списке комнат
*/
int check_links(char *line, t_map *map)
{
	t_room			*start; // комната до знака '-'
	t_room			*tmp; // комната после '-'
	int				len; // длина имени первой комнаты
	t_list_down		*first;
	t_list_down		*second;


	start = map->rooms;

	while (start)
	{
		len = ft_strlen(start->name);
		//пока не нашли название комнаты которая в лайн переходим по списку комнат
		// надо что б len симолов в строке совпадали и комнате, а следующий был '-'
		if (ft_strnequ(start->name, line, len) && ft_strnequ("-", line + len, 1))
		{
			//комнату до '-' нашли, ищем ту что после '-', начиная с начала списка комнат
			tmp = map->rooms;
			while (tmp)
			{
				if (ft_strequ(tmp->name, line + len + 1) && tmp->number != start->number)
				{
					// если нашли комнаты запихиваем в список (для каждой комнаты свой)
					first = ft_list_i_head(start->number, map->link);
					second = ft_list_i_head(tmp->number, map->link);
					ft_list_add_back_i_if_not(&first->next, tmp->number, first->next);
					ft_list_add_back_i_if_not(&second->next, start->number, second->next);
//					ft_list_add_back_i_one(&first->next, tmp->number);
//					ft_list_add_back_i_one(&second->next, start->number);
					return (1);
				}
				tmp = tmp->next;
			}
			return (0);//если комнаты закончились раньше, чем мы её нашли

		}
		start = start->next;
	}
	// если сюда дошли, значит не нашли первую комнату
	return (0);
}

/*
копирует список комнат в столбец смежности
по идее список комнат меняться не будет - можно оставить ссылки (?)
для каждой line, которая не коммент заполняем ссылки
*/
int created_links(char *line, t_map *map)
{
	t_room	*tmp;
	int		st;

	tmp = map->rooms;
	while (tmp)
	{
		ft_list_add_back_down(&map->link, ft_list_new_down(tmp->number));
		tmp = tmp->next;
	}
	st = check_links(line, map);
	if (st)
	{
		ft_str_print_del(&line);

	line = ft_check_cmd(map->fd);
	while (line && st)//get_next_line(map->fd, &line)
	{
		if (!ft_strnequ(line, "#", 1))
			st = check_links(line, map);
		else //значит старт или энд в линках
		{
			ft_str_print_del(&line);
			return (0);
		}
		ft_str_print_del(&line);
		line = ft_check_cmd(map->fd);
	}
	}
	if (st == 0)
		ft_str_print_del(&line);
	return (st);
}