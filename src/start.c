/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:00:58 by qgilbert          #+#    #+#             */
/*   Updated: 2019/07/01 19:00:59 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include "libft.h"

void	ft_lstadd_r(t_room **alst, t_room *new)
{
	if (!alst)
		return ;
	new->next = *alst;
	*alst = new;
}


int		ft_len_int(int num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	if (num == 0)
		return (1);
	return (len);
}


int check_links(char *line, t_map *map)
{//c_room - номер последней комнаты, соответственно комнату на  больше
	//  у комнаты старта #0
	// (void)fd;
	// free(line);
	//МАТРИЦА СМЕЖНОСТИ
	t_room *start;
	t_room *tmp;
	
	int i1;

	int pr;
	int len;
	start = map->rooms;
	// while (start)
	// 	{
	// 		printf("+++%d, %s\n", start->number, start->name);
	// 		start = start->next;
	// 	}
	// 	return (1);

	while (start)
	{
		len = ft_strlen(start->name);
		//пока не нашли название комнаты которая в лайн переходим по списку комнат
		if (ft_strnequ(start->name, line, len) && ft_strnequ("-", line + len, 1))
		{
			//теперь нужно найти номер который после -
			tmp = map->rooms;
			i1 = start->number;
			pr = 0;
			while (tmp && pr == 0)
			{
				if (ft_strequ(tmp->name, line + len + 1))
				{
					map->matr[i1][tmp->number] = 1;
					map->matr[tmp->number][i1] = 1;
					printf("i1 ==== %d\n", i1);
					pr = 1;
					return (1);
				}
				tmp = tmp->next;
			}
			if (pr == 0)//если комнаты закончались раньше, чем мы её нашли
				return (-1);
			//*start = map->rooms;
		}
		start = start->next;
	}
	// если сюда дошли, значит не заполнили матрицу =(
	return (-1);
}

void created_matrix(char *line, t_map *map)
{
	int i;
	int j;
	map->matr = (int**)malloc(sizeof(int*) * (map->c_room + 1));
	i = 0;
	while (i <= map->c_room)
	{
		j = 0;
		map->matr[i] = (int*)malloc(sizeof(int) * (map->c_room + 1));
		while(j <= map->c_room)
			map->matr[i][j++] = 0;
		i++;
	}
	check_links(line, map);
	free(line);
	while (get_next_line(map->fd, &line) && ft_strlen(line) >= 3)
	{
		//printf("ttt%s\n", line);
		if (!ft_strnequ(line, "#", 1))
			check_links(line, map);
		free(line);
	}
	//free(line);
	printf("priwli %d \n", map->c_room);
	i = 0;
	j = 0;

	while (i <= map->c_room)
	{
		j = 0;
		while (j <= map->c_room)
		{
			printf("%d ", map->matr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	check_room(t_map *map)
{
	char *line;
	int status;
	t_room *one_room;
	t_room *last_room;
	t_room *room;

	status = 1;
	room = NULL;
	one_room = NULL;
	last_room = NULL;

	while (get_next_line(map->fd, &line) && ft_strlen(line) >= 3)
	{
		//cat printf("line =  %s\n", line);
		if (ft_strnequ(line, "#", 1))
		{
			if (ft_strequ(line, "##start"))
			{
				free(line);
				get_next_line(map->fd, &line);
				one_room = ft_create_ele(line, 0);
			}
			else if (ft_strequ(line, "##end"))
			{
				free(line);
				get_next_line(map->fd, &line);
				last_room = ft_create_ele(line, -1);
			}
			else
				free(line);
		}
		else if (ft_strstr(line, "-"))//надеюсь этого не может быть в имени!!!
		{
			if (one_room)
			{
				ft_lstadd_r(&map->rooms, one_room);
			}
			else
				return (-1);
			if (last_room)
			{
				last_room->number = status;
				ft_pushback(&map->rooms, last_room);	
			}
			else
				return (-1);
			map->c_room = status;
			created_matrix(line, map);
		}
		else
		{
			room = ft_create_ele(line, status);
			status++;
			ft_lstadd_r(&map->rooms, room);
		}
	}
	return(1);
}



