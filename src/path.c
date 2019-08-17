/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 17:17:03 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/17 17:17:08 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** находим первый путь sh - если его нет что то в ссылках было не валидно
** при первом проходе время первого состояния - длина + с_ant
** в map->two_path->down->next записываем этще путь
** ищем пути, пока получаем выигрыш по времени: main_path_2
*/

int			main_path(t_map *map)
{
	int			k;
	int			win;
	t_list_i	*sh;

	win = 1;
	sh = ft_bfs(map);
	if (sh)
	{
		map->two_path = list_new_down(map->c_ant + ft_list_len_i(sh));
		list_add_down(&map->two_path, list_new_down(ft_list_len_i(sh)));
		map->two_path->down->next = sh;
		k = 1;
		while (map->two_path->down->next && win)
		{
			map->m = 2;
			win = main_path_2(map, ++k);
		}
		return (1);
	}
	else
		return (is_not_valid("no one path"));
}

/*
** ищет заданное кол-во к путей
** если путь выиграшный очищаем предыдущий
*/

/*
** step 2 = del_link_path + ft_new_room
** step 3 = bfs_k_path
*/

/*
** если по новым комнатам нашли путь надо - значит будет существовать к путей
** удаляем реверсные ребра и ищем к путей: ft_bfs_k
*/

int			main_path_2(t_map *map, int k)
{
	t_list_i	*sh_big;
	t_list_i	*sh_k;
	int			win;

	win = 0;
	del_link_path(map);
	sh_big = one_big_path(map);
	ft_new_room(map, sh_big);
	sh_k = bfs_k_path(map, NULL);
	ft_free_list_down(&map->l_new);
	if (sh_k)
	{
		ft_del_shared_path(map, sh_big, sh_k);
		ft_list_add_back_right_down(&map->two_path, ft_bfs_k(map, k));
		if ((win = ft_check_path_n(map->two_path, map)))
		{
			map->two_path->right->content = win;
			if (win > 0)
				ft_free_first_in_two_path(&map->two_path);
			ft_free_list_down(&map->l_new);
		}
	}
	ft_free_list_i(&sh_k);
	ft_free_list_i(&sh_big);
	return (win);
}

/*
** удалить нужно все ссылки состоянниея 1-ого(текущего), всех путей которые есть
** 1 - в map->l_new записываем копию всех ссылок, что б не потерять оригинал
** 2 - tek_down - копия всех путей состояния
** 3 - tek_down_start для очистки копии списка  down
** 4 - tek_path_start для очистки листа
** В l_new удаляем все пути состояния
*/

void		del_link_path(t_map *map)
{
	t_list_down	*tek_down;
	t_list_down	*tek_down_start;
	t_list_i	*tek_path;
	t_list_i	*tek_path_start;

	map->l_new = ft_copy_list_down(map->link);
	tek_down = ft_copy_list_down(map->two_path->down);
	tek_down_start = tek_down;
	while (tek_down)
	{
		tek_path = ft_list_copy_i(tek_down->next);
		tek_path_start = tek_path;
		while (tek_path && tek_path->next)
		{
			del_lst_if(&(i_head(tek_path->cnt, map->l_new)->next),
				tek_path->next->cnt);
			tek_path = tek_path->next;
		}
		ft_free_list_i(&tek_path_start);
		tek_down = tek_down->down;
	}
	ft_free_list_down(&tek_down_start);
}

t_list_i	*one_big_path(t_map *map)
{
	t_list_down	*tek_down;
	t_list_i	*tek_path;
	t_list_i	*big_path;

	tek_down = map->two_path->down;
	big_path = ft_list_new_i(tek_down->next->cnt);
	while (tek_down)
	{
		tek_path = tek_down->next;
		while (tek_path)
		{
			if (tek_path->cnt > 0)
				list_add_i1(&big_path, tek_path->cnt);
			tek_path = tek_path->next;
		}
		tek_down = tek_down->down;
	}
	return (big_path);
}
