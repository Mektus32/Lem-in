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

void	ft_pri_cop(t_map *map)
{
	t_list_down	*tmp;
	t_list_i	*right;
	int 		i;

	i = 0;
	tmp = map->link_new;
	while (tmp)
	{
		ft_printf("room[%d]->", tmp->content);
		right = tmp->next;
		while (right)
		{
			ft_printf("%d->", right->content);
			right = right->next;
//			i++;
//			if (i == 15)
//				return ;
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
	int k;// счетчик массива d
	int n_ant; //временное кол- во муравьев
	int c_path;//кол-во путей
	int f;//не знаю как избавиться от бесконечного цикла
	int t1;//время предыдушего пути
	int t_now;
	int len_max;//максимальная длина в массиве

	t1 = two_path->content;
	//кол-во путей в новом стостоянии
	path_new = two_path->right;
	//path_new->content; пока равен 0, надо перезаписать тужа время
	c_path = ft_list_len_down(path_new);
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
	t_now = len_max + n_ant/c_path + ((n_ant == 0) ? 0 : 1);
	if (t_now < t1)//выбираем этот путь
		return (t_now);
	return (0);
}

void pr_list(t_list_i *new)
{
	while (new)
	{
		printf("l_c = %d, ",new->content);
		new = new->next;
	}
	printf("\n");
}

void ft_new_room(t_map *map, t_list_i *sh)
{
	t_list_down *tek_down;
	t_list_i *in;//c_room + номер комнаты
	int 	tek_content;
	t_list_i *tek_next;
	t_list_i *sh_tmp;
	int r_pred;

	r_pred = sh->content;
	//исключая первую и последнюю вершину
	sh = sh->next;
	! tmp
	while (sh->next)
	{
		sh_tmp = sh;
		//проверяем комнату в пути
		//если оставшихся связей больше 1, удаляем существующую и заменяем 2умя новыми (in - out)
		if (ft_list_len_i(ft_list_i_head(sh->content, map->link_new)->next) > 1)
		{
			//tek_i = ft_list_i_head(sh->content, map->link_new)->next;

			// в 2 новые записываем существовавшие связи
			//in = ft_list_new_i(sh->content + map->c_room);

			// добавить ИН - комнату в лист линк нью
			ft_list_add_back_down(&map->link_new, ft_list_new_down(sh->content + map->c_room));
			// в конец исходного СС - нынешнего АУТ добавим ИН
			ft_list_add_back_i(&(ft_list_i_head(sh->content, map->link_new)->next), ft_list_new_i(sh->content + map->c_room));
			//должна удалить из АУТА в след комнату на пути
			ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_new)->next) , sh->next->content);
			//вместо неё должна из нового ин идти в старую комнату(предыдущую) пути
			//больше из ИН ничего не выходит
			ft_list_add_back_i(&(ft_list_i_head(sh->content + map->c_room, map->link_new)->next), ft_list_new_i(r_pred));

			// (для всех комнат, которые ссфлались на текущую - заменить на ссылание в ИН)
			// а ссылку на тукущую из комнаты убрать
			tek_down = map->link_new;
			//ПОКА есть комнаты в СС
			int i;
			i = 0;
			//проверяем только связи которые были до добавления новой комнаты
			while (i <= map->c_room)
			{
				tek_content = tek_down->content;//комната из которой ищем ссылки
				tek_next = tek_down->next;//список в котором ищем ссылки на комнату из пути, что б поменять их на ин
				while(tek_next)
				{

					//если была связь на комнату
					if (tek_next->content == sh->content )//&&  tek_content <= map->c_room
					{
						// перезапишим старую связь в новую комнату
						//ft_list_add_back_i(&(ft_list_i_head(sh->content +  map->c_room, map->link_new)->next), ft_list_new_i(tek_content));
						//и из комныты запишем на ИН
						ft_list_add_back_i(&(ft_list_i_head(tek_content, map->link_new)->next),ft_list_new_i(sh->content + map->c_room));
						//из комнаты удалим на АУТ
						ft_remove_list_if(&(ft_list_i_head(tek_content, map->link_new)->next) , sh->content);
						//
						//ft_remove_list_if(&(ft_list_i_head(tek_content, map->link_new)->next) , sh->content + map->c_room);

//						while (sh_tmp)
//						{
//							ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_new)->next) , sh_tmp->content);
//							sh_tmp = sh_tmp->next;
//						}
						//break ;
					}
					tek_next = tek_next->next;
				}
				tek_down = tek_down->down;

				i++;
			}
		}
			//printf("c = %d, len = %d...", sh->content, ft_list_len_i(ft_list_i_head(sh->content, map->link_new)->next));
		r_pred = sh->content;
		sh = sh->next;
	}
}

int main(int ac, char	**av)
{
	int		fd;
	t_map	*map;
	char	*str;
	t_list_i *sh;
	t_list_i *sh_1;//копия
	t_list_i *link;//связи ля конкретной комнаты

	//str = "/Users/ojessi/Desktop/Arina/test_3";//;ac;
	str = "/Users/qgilbert/Desktop/lem_in/five/School21-Lem-in/a_test";
	//str = av[1];
	map = (t_map*)malloc(sizeof(t_map));
	map->rooms = NULL;
	map->link = NULL;
	map->sh = NULL;
	map->two_path = NULL;
	fd = open(str, O_RDONLY);
	if (make_map(fd, map) && check_room(map))
	{
		sh = ft_bfs(map);
		sh_1 = ft_list_copy_i(sh);
//		//вместо следующей надо использовать добавление при движении вправо!!
//		ft_list_add_back_right_down(&map->two_path, ft_list_new_down(ft_list_len_i(sh)));
//		ft_list_add_back_down(&map->two_path, ft_list_new_pointer_down(sh));

//		ft_pri_sh(map);
		ft_pri(map);
		map->link_new = ft_copy_list_down(map->link);
		ft_printf("\n\n");
//		ft_pri_cop(map);

		while(sh->next)
		{
			ft_printf("ppp - %d  ", sh->content);
			ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_new)->next), sh->next->content);
			sh = sh->next;
		}
		//надо добавить в линк новых комнат (ин-аут)
		//
		ft_new_room(map, sh_1);
		ft_printf("\n\n");
		ft_pri_cop(map);
		//ft_bfs_k(map, 2);
	}
	else// и все почистить бы
	{

		ft_printf("ERROR");
	}
	return (0);
}
//room[0]->1->
//room[1]->0->2->
//room[2]->1->10->
//room[3]->2->5->11->10->
//room[4]->0->5->11->
//room[5]->6->11->10->
//room[6]->5->7->
//room[7]->3->6->
//room[11]->3->5->
//room[10]->2->5->


//room[0]->1->
//room[1]->0->2->
//room[2]->1->10->
//room[3]->2->5->11->10->
//room[4]->0->5->11->
//room[5]->6->11->10->
//room[6]->5->7->
//room[7]->6->10->
//room[11]->3->5->
//room[10]->2->5->7->
//at-h6%
