//удалить нужно все ссылки состоянниея 1-ого, всех путей которые есть
void	del_link_path(t_map *map)
{
	t_list_down *tek_down;
	t_list_i	*tek_path;

	//сделаем копию всех оригинальных ссылок
	map->link_new = ft_copy_list_down(map->link);
	//пока есть пути (down) 
	tek_down = map->two_path->down;
	while(tek_down)
	{
		tek_path = tek_down->next;
		while (tek_path->next)
		{
			ft_remove_list_if(&(ft_list_i_head(tek_path->content, map->link_new)->next), tek_path->next->content);
			tek_path = tek_path->next;
		}
		tek_down = tek_down->down;
	}
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
		tek_path = tek_down->next->next;
		while (tek_path->next)
		{
			ft_list_add_back_i(&big_path, ft_list_new_i(tek_path->content));
			tek_path = tek_path->next;
		}
		tek_down = tek_down->down;
	}
	ft_list_add_back_i(&big_path, ft_list_new_i(tek_path->content));
	return (big_path);
}
