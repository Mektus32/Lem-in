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


void	ft_pri(t_map *map)
{
	t_list_down	*tmp;
	t_list_i	*right;

	tmp = map->link;
	while (tmp)
	{
		ft_printf("room[%d]->", tmp->content);
		right = tmp->next;
		while (right)
		{
			ft_printf("%d->", right->content);
			right = right->next;
		}
		ft_printf("\n");
		tmp = tmp->down;
	}
}

//принт путь
void	ft_pri_sh(t_map *map)
{
	t_list_i	*sh;

	sh = map->sh;
	ft_printf("sh = ");
	while (sh)
	{
		ft_printf("%d-", sh->content);
		sh = sh->next;
	}
	ft_printf("\n");
}


int ft_check_path_n(t_list_down *two_path, t_map *map)
{
	t_list_down *path_new;
	int *d;//массив длин путей текущего состояния
	int n_ant; //временное кол- во муравьев
	int c_path;
	int f;//не знаю как избавиться от бесконечного цикла
	int t1;//время предыдушего пути
	int t_now;

	t1 = two_path->content;
	//кол-во путей в новом стостоянии
	path_new = two_path->next;
	//path_new->content; пока равен 0, надо перезаписать тужа время
	c_path = len_down(path_new);
	//
	d = (int *)malloc(sizeof(int) * c_path);
	path_new = path_new->down;
	//переходим к 1ому пути в состоянии
	k = 0;
	//заполним длины из структуры
	while (path_new)
	{
		d[k++] = path_new->content;
		path_new = path_new->down;
	}
	n_ant = map->c_ant;
	len_max = ft_max_mass(d);
	// до равновесия заполним все пути муравьями
	f = 1;
	while (n_ant > 0 && f)
	{
		k = 0;
		f = 0;// что б знать что мы продолжаем муравьев раскидывать
		while (d[k] && n_ant)
		{
			if (d[k] < len_max)
			{
				d[k] += 1;
				n_ant--;
				f++;
			}
			k++;
		}
	}
	//время которое потребуется для прохода этого состояния
	//округляет инт к меньшему значению
	//добавляем 1, если колличество муравьев не 0 осталось
	t_now = len_max + n_ant/c_path + (n_ant == 0) ? 0 : 1;
	if (t_now < t1)//выбираем этот путь
		return (1);
	return (0);
}

int main(int ac, char	**av)
{
	int		fd;
	t_map	*map;
	char	*str;
	t_list_i *sh;

	//str = "/Users/qgilbert/Desktop/lem_in/five/School21-Lem-in/test_4";//;ac;
	str = av[1];
	map = (t_map*)malloc(sizeof(t_map));
	map->rooms = NULL;
	map->link = NULL;
	map->sh = NULL;
	fd = open(str, O_RDONLY);
	if (make_map(fd, map) && check_room(map))
	{
		// теперь нужен поиск в ширину
		ft_pri(map);
		//ft_bfs(map);
		ft_bfs(map);
		ft_pri_sh(map);
		ft_list_revers(&map->sh);
		sh = map->sh;
		while(sh)
		{
			printf("%d - ", sh->content);
			sh = sh->next;
		}
		//проверить достаточно ли путей для муравьев
		ft_check_path_n(t_list_down);

		//удалить связи, которые есть в списке

	}
	else// и все почистить бы
	{

		ft_printf("ERROR");
	}
	return (0);
}
