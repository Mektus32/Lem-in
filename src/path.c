#include "lem_in.h"

void main_path(t_map *map)
{
	int			k; //кол-во путей
	t_list_i	*sh;
	t_list_i	*sh_big;
	t_list_i	*sh_2;
	int			win;

	win = 1;
	sh = ft_bfs(map);

	//при первом проходе длина время первого стостояния
	map->two_path = ft_list_new_down(map->c_ant + ft_list_len_i(sh));
	ft_list_add_back_down(&map->two_path, ft_list_new_down(ft_list_len_i(sh)));
	map->two_path->down->next = sh;
	// пытаемся найти новый путь, если получаем выигрыш - продолжаем
	k = 1;
	while (map->two_path->down->next && win)
	{
		k++;
		del_link_path(map);
		// можно ж перезаписать большой путь сюда
		sh_big = one_big_path(map);
		ft_new_room(map, sh_big);
		sh_2  = bfs_k_path(map, NULL);
		//ГДЕТО РЕВЕРСНУТЬ ПУТЬ НАДО
		if (sh_2)
		{
			ft_del_shared_path(map, sh_big, sh_2);
			ft_list_add_back_right_down(&map->two_path, ft_bfs_k(map, k));
			if ((win = ft_check_path_n(map->two_path, map)))
			{
				ft_printf("win = %d\n", win);
				map->two_path->right->content = win;
				//удаляем предыдущее состояние
				if (win > 0)
				{
					ft_free_first_in_two_path(&map->two_path);
					ft_free_list_i(&sh_big);
					ft_free_list_i(&sh_2);
				}
			}
		}
		else
		{
			ft_free_list_i(&sh_big);
			return ;
		}

	}
}

//удалить нужно все ссылки состоянниея 1-ого, всех путей которые есть
void	del_link_path(t_map *map)
{
	t_list_down *tek_down;
	t_list_down *tek_down_start;
	t_list_i	*tek_path;
	t_list_i	*tek_path_start;


	//сделаем копию всех оригинальных ссылок
	map->link_new = ft_copy_list_down(map->link);
	//пока есть пути (down) 
	tek_down = ft_copy_list_down(map->two_path->down);
	tek_down_start = tek_down;
	while(tek_down)
	{
		tek_path = ft_list_copy_i(tek_down->next);//tek_down->next;//tek_path = ft_list_copy_i(tek_down->down->next);
		tek_path_start = tek_path;
		while (tek_path && tek_path->next)
		{
			ft_remove_list_if(&(ft_list_i_head(tek_path->content, map->link_new)->next), tek_path->next->content);
			tek_path = tek_path->next;
		}
		ft_free_list_i(&tek_path_start);
		tek_down = tek_down->down;
	}
	ft_free_list_down(&tek_down_start);
}

//общий путь без повторения первой и последней комнаты, для всех путей состояни
t_list_i *one_big_path(t_map *map)
{
	t_list_down *tek_down;
	t_list_i	*tek_path;
	t_list_i	*big_path;

	
	//пока есть пути (down) 
	tek_down = map->two_path->down;
	big_path = ft_list_new_i(tek_down->next->content);
	while(tek_down)
	{
		tek_path = tek_down->next;
		while (tek_path)
		{
			ft_list_add_back_i(&big_path, ft_list_new_i(tek_path->content));
			tek_path = tek_path->next;
		}
		tek_down = tek_down->down;
	}
	return (big_path);
}
