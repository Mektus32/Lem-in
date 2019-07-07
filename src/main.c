/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:16:18 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/30 17:16:19 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//Колличество муравьев первой строкой - не предусмотрено
// Если в name "-" хз что делать
// пока нет проверки на невалидные данные - но надо просто ретернуть -1 всегда или НАЛ если структура

t_room	*ft_create_ele(char *line, int number)
{
	int i;
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	i = 0;
	while (line[i] != ' ')
		i++;
	room->name = (char*)malloc(sizeof(char) * i + 1);
	room->name[i] = '\0';
	ft_strncpy(room->name, line, i);
	room->x = ft_atoi(line + i);
	room->y = ft_atoi(line + ft_len_int(room->x) + i);
	room->number = number;
	room->next = NULL;
	room->dist = 0;
	room->par_num = -1;

	free(line);
	return (room);
}

void ft_pushback(t_room **head, t_room *new)
{
	t_room *list;

	if (!head)
		return ;
	list = *head;
	if (*head)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
}


void 	make_map(int fd, t_map *map)
{
	map->fd = fd;
	map->c_room = 0;//кол - во комнат
	map->matr = NULL;//матрица смежности
	map->rooms = NULL;//лист всех комнат
}

int main(int ac, char	**av)
{
	int fd;
	t_map *map;
	int status;
	//t_room *rooms;
	t_list_i *tmp;

	map = (t_map*)malloc(sizeof(t_map));
	if (ac > 0)
	{
		fd = open(av[1], O_RDONLY);
		//*map->rooms = 0;
		make_map(fd, map);
		check_room(map);
		//printf("st = %d\n", check_room(map));
	// теперь нужен поиск в ширину
	status = ft_bfs(map);
	printf("status = %d\n", status);
	}
	int i;
	i = 0;
	while (map->matr[i])
	{
		printf("i = %d\n", i);
		tmp = map->matr[i];
		while (tmp)
		{
			printf("n - %d\n", tmp->content);
			tmp = tmp->next;
		}
		i++;
	}

	// rooms = map->rooms;
	// while(rooms)
	// {
	// 	printf("num = %d,  dist = %d\n", rooms->number,  rooms->dist);
	// 	printf("name_par = %d, dist = %d\n", rooms->par_num, rooms->dist);
	// 	rooms = rooms->next;
	// }
	tmp = map->sh;
	printf("path:\n");
	while (tmp)
	{
		printf("%d ", tmp->content);
		tmp = tmp->next;
	}

	return (0);
}
