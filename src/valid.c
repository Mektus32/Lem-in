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

	map->fd = fd;
	map->len_sh = 0;
	map->c_room = 0;//кол - во комнат
	map->rooms = NULL;//лист всех комнат
	if (get_next_line(map->fd, &line) == 1)
	{
		//ft_printf("%s\n", line);
		i = 0;
		while (ft_isdigit(line[i]))
			i++;
		// если кол-во чисел не совпадает с длинной строки
		// кидаем ошибку.
		// длина строки не может быть 0 тут, тк гнл вернул нам 1
		/* Ты уверена что не может быть такого что там просто пробелы, которые не играют роли? */
		if ((int)ft_strlen(line) == i)
		{
			map->c_ant = ft_atoi(line);
			// if (map->c_ant == 0)
			// мне все-таки кажется, что ошибка /* Согласен */
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&line);
		return (0);
	}
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
	while (get_next_line(map->fd, &line) > 0 && ft_strlen(line) >= 3)/* Почему именно 3? минимум же 5 получается, 3 символа и два пробела */
	{
		//ft_printf("%s\n", line);
		if (ft_strnequ(line, "#", 1))
		{
			if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			{
				if (ft_strequ(line, "##start") == 1)
				{//добавляем в начало сразу
					ft_strdel(&line);
					if (get_next_line(map->fd, &line) > 0)
					{
						//ft_printf("%s\n", line);
						ft_list_add_room(&map->rooms, ft_create_ele(line, 0));
					}
					else
					{


						return (0);
					}
				}
				else
				{
					ft_strdel(&line);
					if (get_next_line(map->fd, &line) > 0)
					{
						//ft_printf("%s\n", line);
						last_room = ft_create_ele(line, -1);
					}
					else
						return (0);
				}
			}
			else
				ft_strdel(&line);
		}
		/* Вместо ft_strstr наверное логичнее ft_strchr использовать */
		else if (ft_strchr(line, '-') && ft_strchr(line, ' ') == NULL)
		{
			if (last_room) 
			{
				last_room->number = number;
				ft_push_back_room(&map->rooms, last_room);
			}
			else
				return (0);
			map->c_room = number;
			// до ссылок все прошло успешно, переходим к ссылкам
			return (created_links(line, map));
		}
		else
		{
			ft_push_back_room(&map->rooms, ft_create_ele(line, number));
			number++;
		}
	}
	return (0);
}

/*
ф. вызывается для каждой входной строки, где есть - и нет ' '
заполняет ссылки в две стороны
*/
int check_links(char *line, t_map *map)
{
	t_room			*start; // комната до знака '-'
	t_room			*tmp; // комната после '-'
	int				len; // длина имени первой комнаты
	t_list_down		*first;
	t_list_down		*second;


	start = map->rooms;
	//находим комнату из строки до '-' во всем списке комнат
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
				if (ft_strequ(tmp->name, line + len + 1))
				{
					// если нашли комнаты запихиваем в список (для каждой комнаты свой)
					first = ft_list_i_head(start->number, map->link);
					second = ft_list_i_head(tmp->number, map->link);
					ft_list_add_back_i(&first->next, ft_list_new_i(tmp->number));
					ft_list_add_back_i(&second->next, ft_list_new_i(start->number));
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
	int		st; // - статус, если что-то пошло не так в лайнах, вернем ошибку (0)
	//создаем новый список под СТОЛБЕЦ
	/* Ты опять создала массив, а ниже к нему обращаешься как к списку(при добавлении/копированиии элементов) */
	/*
	 * map->link = (t_list_down*)malloc(sizeof(t_list_down) * (map->c_room + 1));
	 * i = 0;
	 * //переписываем в список столбцов список комнат
	 * while (i <= map->c_room)
	 * {
	 * 		ft_list_add_back_down(&map->link, ft_list_new_down(map->rooms->number));
	 * 		map->rooms = map->rooms->next;
	 * 		i++;
	 * }
	 */
	tmp = map->rooms;
	while (tmp)
	{
		ft_list_add_back_down(&map->link, ft_list_new_down(tmp->number));
		tmp = tmp->next;
	}
	st = check_links(line, map);
	ft_strdel(&line);
	while (get_next_line(map->fd, &line) && st)
	{
		//ft_printf("%s\n", line);
		if (!ft_strnequ(line, "#", 1))
			st = check_links(line, map);
		ft_strdel(&line);
	}
	return (st);
}
//