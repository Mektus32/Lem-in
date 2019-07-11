// заполним начальнуб струкруру map 
// проверим на валидность первую строку (кол-во муравьев)
// ? если муравьев 0 кидать ошибку?
int		make_map(int fd, t_map *map)
{
	char *line;
	int		i;

	map->fd = fd;
	map->c_room = 0;//кол - во комнат
	map->rooms = NULL;//лист всех комнат
	if (get_next_line(map->fd, &line) == 1)
	{
		i = 0;
		while (ft_isdigit(line[i]))
			i++;
		// если кол-во чисел не совпадает с длинной строки
		// кидаем ошибку.
		// длина строки не может быть 0 тут, тк гнл вернул нам 1
		if (ft_strlen(line) == i)
		{
			map->c_ant = ft_atoi(line);
			// if (map->c_ant == 0)
			// мне все-таки кажется, что ошибка		
			return (1);
		}
		else
			return (0);
		free(line);
	}
	else
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
	char *line;
	int number;
	t_room *last_room;

	number = 1;
	last_room = NULL;
	while (get_next_line(map->fd, &line) && ft_strlen(line) >= 3)
	{
		if (ft_strnequ(line, "#", 1))
		{
			if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			{
				free(line);
				get_next_line(map->fd, &line);
				if (ft_strequ(line, "##start") == 1) //добавляем в начало сразу
					ft_lstadd_r(&map->rooms, ft_create_ele(line, 0));
				else
					last_room = ft_create_ele(line, -1);
			}
			else
				free(line);
		}
		else if (ft_strstr(line, "-") && ft_strstr(line, " ") == NULL)
		{
			if (last_room) 
			{
				last_room->number = number;
				ft_pushback(&map->rooms, last_room);	
			}
			else
				return (0);
			map->c_room = number;
			// до ссылок все прошло успешно, переходим к ссылкам
			return (created_matrix(line, map));
		}
		else
		{
			ft_lstadd_r(&map->rooms, ft_create_ele(line, number));
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
	t_room *start; // комната до знака '-'
	t_room *tmp; // комната после '-'
	int len; // длина имени первой комнаты

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
					ft_lstaddback_i(ft_list_i_head(start->number, &map->link), ft_lstnew_i(tmp->number));
					ft_lstaddback_i(ft_list_i_head(tmp->number, &map->link), ft_lstnew_i(start->number));
					pr = 1;
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
	int i;
	int st; // - статус, если что-то пошло не так в лайнах, вернем ошибку (0)
	//создаем новый список под СТОЛБЕЦ
	map->link = (t_list_down*)malloc(sizeof(t_list_down) * (map->c_room + 1));
	i = 0;
	//переписываем в список столбцов список комнат
	while (i <= map->c_room)
	{
		ft_lstaddback_down(&map->link, ft_lstnew_down(map->rooms->content));
		map->rooms = map->rooms->next;
		i++;
	}
	st = check_links(line, map);
	free(line);
	while (get_next_line(map->fd, &line) && st)
	{
		if (!ft_strnequ(line, "#", 1))
			st = check_links(line, map);
		free(line);
	}
	return (st);
}