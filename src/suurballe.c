#include "lem_in.h"

void ft_new_room(t_map *map, t_list_i *sh)
{
	t_list_down *tek_down;
	t_list_i *in;//c_room + номер комнаты
	int 	tek_content;
	t_list_i *tek_next;
	t_list_i *sh_tmp;
	int r_pred;//предыдущее значение пути

	r_pred = sh->content;
	//исключая первую и последнюю вершину
	sh = sh->next;
	//! tmp
	while (sh->next)
	{
		sh_tmp = sh;
		//проверяем комнату в пути
		//если оставшихся связей больше 1, удаляем существующую и заменяем 2умя новыми (in - out)
		if (ft_list_len_i(ft_list_i_head(sh->content, map->link_new)->next) > 1)
		{
			// добавить ИН - комнату в лист линк нью
			ft_list_add_back_down(&map->link_new, ft_list_new_down(sh->content + map->c_room));
			// в конец исходного СС - нынешнего АУТ добавим ИН
			ft_list_add_back_i(&(ft_list_i_head(sh->content, map->link_new)->next), ft_list_new_i(sh->content + map->c_room));
			//должна удалить из АУТА в пред комнату на пути - эта связь теперь из ИН (след.действие)
			ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_new)->next) , r_pred);
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
				//если была связь на комнату и комната не следующая в пути
					if (tek_next->content == sh->content &&  tek_content != sh->next->content)//
					{
						// перезапишим связь из ссылки на АУТ в новую комнату - ссулку на ИН
						ft_list_add_back_i(&(ft_list_i_head(tek_content, map->link_new)->next),ft_list_new_i(sh->content + map->c_room));
						//из комнаты удалим на АУТ
						ft_remove_list_if(&(ft_list_i_head(tek_content, map->link_new)->next), sh->content);
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
//путь вролде в реверсном состоянии ?
//найдем общие ребра и удалим из link_copy
void ft_del_shared_path(t_map *map, t_list_i *sh, t_list_i *rev_2)
{
	t_list_i	*rev_2_c;
	ft_list_revers(&rev_2);


	while (sh->next)
	{
		rev_2_c = ft_list_copy_i(rev_2);
		while (rev_2_c->next)
		{

			//если текущее и след совпадают
			if (sh->content == rev_2_c->content && sh->next->content == (rev_2_c->next->content))
			{	//удаляем одинаковые ребра из пути
				ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_copy)->next), sh->next->content);
				printf("da %d, %d", sh->content, sh->next->content);
			}
			rev_2_c = rev_2_c->next;
		}
		//ft_free_list_i(&rev_2_c);
		sh = sh->next;
	}
	//удаляем связи где комнаты ин и аут
	ft_free_list_down(&map->link_new);
	map->link_new = ft_copy_list_down(map->link_copy);
}