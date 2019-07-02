int check_links(char *line, t_map *map)
{//c_room - номер последней комнаты, соответственно комнату на  больше
	//  у комнаты старта #0
	// (void)fd;
	// free(line);
	//МАТРИЦА СМЕЖНОСТИ
	t_rlist *start;
	t_rlist *tmp;
	
	int i1;
	int len;
	int pr;

	*start = map->rooms;
	while (*start)
	{
		len = ft_strlen(start->name);
		//пока не нашли название комнаты которая в лайн переходим по списку комнат
		if (ft_strnequ(start->name, line, len) && ft_strnequ("-", line + len, 1))
		{
			//теперь нужно найти номер который после -
			*tmp = map->rooms;
			i1 = start->number;
			pr = 0;
			while (*tmp && pr == 0)
			{
				if (ft_strequ(tmp->name, line + len + 1))
				{
					map->matr[i1][tmp->number] = 1;
					map->matr[tmp->number][i1] = 1;
					pr = 1;
					return (1);
				}
				*tmp = *tmp->next;
			}
			if (pr == 0)//если комнаты закончались раньше, чем мы её нашли
				return (-1);
			//*start = map->rooms;
		}
		*start = start->next;
	}
	// если сюда дошли, значит не заполнили матрицу =(
	return (-1);
}

void created_matrix(char *line, t_map *map)
{
	int	**matr;

	map->matr = (int**)malloc(sizeof(int*) * (map->c_room + 1));
	i = 0;
	while (i <= map->c_room)
	{
		map->matr[i++] = (int*)malloc(sizeof(int) * (map->c_room + 1));
	}
	check_links(line, map);
	free(line);
	while (get_next_line(map->fd, &line) && ft_strlen(line) > 3)
	{
		if (!ft_strnequ(line, "#", 1))
			check_links(line, map);
		free(line);
	}
}

