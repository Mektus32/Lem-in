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
	map->two_path = NULL;
	fd = open(str, O_RDONLY);
	if (make_map(fd, map) && check_room(map))
	{
		sh = ft_bfs(map);
		//вместо следующей надо использовать добавление при движении вправо!!
		ft_lstaddback_down(&map->two_path, ft_lstnew_down(ft_listlen_i(sh)));
		ft_lstaddback_down(&map->two_path, ft_lstnewpointer_down(sh));
		// теперь нужен поиск в ширину
		//ft_pri(map);
		//ft_bfs(map);
		//ft_bfs(map);
		//ft_pri_sh(map);
		//while(sh)
		//{
		//	printf("%d - ", sh->content);
		//	sh = sh->next;
		//}
		//проверить достаточно ли путей для муравьев

		//удалить связи, которые есть в списке

	}
	else// и все почистить бы
	{

		ft_printf("ERROR");
	}
	return (0);
}
