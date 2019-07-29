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

int main(int ac, char	**av)
{
	int		fd;
	t_map	*map;
	char	*str;
	t_list_i *sh;
	t_list_i *sh_2;
	t_list_i *sh_1;//копия
	t_list_i *link;//связи ля конкретной комнаты

	str = "../test_3";
	//str = av[1];
	map = (t_map*)malloc(sizeof(t_map));
	map->rooms = NULL;
	map->link = NULL;
	map->sh = NULL;
	map->two_path = NULL;
	fd = open(str, O_RDONLY);
	if (make_map(fd, map) && check_room(map))
	{
		main_path(map);
// 		sh = ft_bfs(map);
// 		sh_1 = ft_list_copy_i(sh);
// //		//вместо следующей надо использовать добавление при движении вправо!!
// //		ft_list_add_back_right_down(&map->two_path, ft_list_new_down(ft_list_len_i(sh)));
// //		ft_list_add_back_down(&map->two_path, ft_list_new_pointer_down(sh));

// //		ft_pri_sh(map);
// 		ft_pri(map);
// 		map->link_new = ft_copy_list_down(map->link);
// 		map->link_copy = ft_copy_list_down(map->link);

// 		ft_printf("\n\n");
// //		ft_pri_cop(map);

// 		while(sh->next)
// 		{
// 			ft_printf("ppp - %d  ", sh->content);
// 			ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_new)->next), sh->next->content);
// 			sh = sh->next;
// 		}
// 		//надо добавить в линк новых комнат (ин-аут)
// 		//
// 		ft_new_room(map, sh_1);
// 		ft_printf("\n\n");
// 		ft_pri_cop(map);
// 		// надо найти одинаковые ребра (разумеется, разнонаправленные и удалить их - в map->link_copy)
// 		sh_2  = bfs_k_path(map, NULL, NULL);
// //printf("sh_1 = \n");
// //pr_list(sh_1);
// //
// //		printf("sh_2 = \n");
// //		pr_list(sh_2);
// //изменяет линк копи   map->link_new = ft_copy_list_down(map->link_copy);
// 		ft_del_shared_path(map, sh_1, bfs_k_path(map, NULL, NULL));


// 		printf("new_path  = \n");
// 		ft_pri_cop(map);
// 		t_list_down *path_2;

// 		//Два путя не ищет в новом графе
// 		//path_2 = ft_bfs_k(map, 2);
		ft_printf("=============");
 		ft_print_all_path(map->two_path);
		ant_in_room(map);
// 		// НАДО ЕЩЕ ПРОЙТИ БФСОМ для нахождения нового пути
	}
	else// и все почистить бы
	{
		ft_printf("ERROR");
	}
	return (0);
}

