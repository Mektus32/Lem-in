#include "lem_in.h"

/*
 * изменение ссылок
 * 1. все комнаты которые ссылались на нашу (АУТ теперь) - теперь ссылаются на ИН
 *  из комнаты аут ссылка теперь только в ИН
 * 2. из комнаты больше нет ссылок на АУТ
 * итерируемся только по i <= map->c_room
 * tek_next - список в котором ищем ссылки на комнату из пути, что б поменять их на ин
 * СВЯЗИ перезаписываем ЕСЛИ комната не СЛЕД В ПУТИ tek_content != sh->next->content
 * */
static void    ft_new_link_in(t_map *map, t_list_i *sh)
{
    int         i;
    int         tek_content;
    t_list_down *tek_down;
    t_list_i    *tek_next;

    i = 0;
    tek_down =  map->link;
    while (i <= map->c_room)
    {
        tek_content = tek_down->content;
        tek_next = tek_down->next;
        while(tek_next)
        {
            if (tek_next->content == sh->content &&  tek_content != sh->next->content)//
            {
                ft_list_add_back_i_one(&(ft_list_i_head(tek_content, map->link_new)->next),
                        sh->content + map->c_room);
                ft_remove_list_if(&(ft_list_i_head(tek_content, map->link_new)->next), sh->content);
            }
            tek_next = tek_next->next;
        }
        tek_down = tek_down->down;
        i++;
    }
}

/* условие замены/удаления: если оставшихся связей больше 1
 * добавляет новые комнаты в link_new (ИН комнаты)
 *
 * нынешние комнаты в пути заменяем комнатами АУТ
 *  при обхоже игнорируем комнату end и start (sh = sh->next и while (sh->next))
 *  r_pred - номер пред. комнаты
 *  ft_new_link_in - меняет ссылки в link_new
*/
void    ft_new_room(t_map *map, t_list_i *sh)
{
    int         r_pred;

	r_pred = sh->content;
	sh = sh->next;
	while (sh->next)
	{
		if (ft_list_len_i(ft_list_i_head(sh->content, map->link_new)->next) > 1 && sh->content != 0 &&
		sh->content != map->c_room)
		{
			// добавить ИН - комнату в лист линк нью
			ft_list_add_back_down(&map->link_new, ft_list_new_down(sh->content + map->c_room));
			// в конец исходного СС - нынешнего АУТ добавим ИН
			ft_list_add_back_i_one(&(ft_list_i_head(sh->content, map->link_new)->next),
					(sh->content + map->c_room));
			//должны удалить из АУТА в пред комнату на пути - эта связь теперь из ИН (след.действие)
			ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_new)->next) , r_pred);
			//вместо неё должна из нового ин идти в старую комнату(предыдущую) пути
			//больше из ИН ничего не выходит
			ft_list_add_back_i_one(&(ft_list_i_head(sh->content + map->c_room, map->link_new)->next), r_pred);
			// (для всех комнат, которые ссфлались на текущую - заменить на ссылание в ИН)
			// а ссылку на тукущую из комнаты убрать
            ft_new_link_in(map, sh);
			//ПОКА есть комнаты в СС
			//проверяем только связи которые были до добавления новой комнаты
		}
		r_pred = sh->content;
		sh = sh->next;
	}
}
/*
 * step 5
 * заполняем новый link_new
 * удвляет реверсные ребра, но по-моему тут лишний промежкуточный link_copy
 * может можно сразу в линк нью записывать
 * */
void ft_del_shared_path(t_map *map, t_list_i *sh, t_list_i *rev_2)
{
	t_list_i	*rev_2_c;
	t_list_i	*rev_start;

	//map->link_copy = ft_copy_list_down(map->link);
	map->link_new = ft_copy_list_down(map->link);
	rev_2_c = ft_list_copy_i(rev_2);
	ft_list_revers(&rev_2_c);
	rev_start = rev_2_c;
	while (sh->next)
	{
		rev_2_c = rev_start;
		while (rev_2_c->next)
		{
			//если текущее и след совпадают
			if (sh->content == rev_2_c->content && sh->next->content == (rev_2_c->next->content))
			{
				ft_remove_list_if(&(ft_list_i_head(sh->content, map->link_new)->next), sh->next->content);
				ft_remove_list_if(&(ft_list_i_head(sh->next->content, map->link_new)->next), sh->content);
			}
			rev_2_c = rev_2_c->next;
		}
		sh = sh->next;
	}
	//удаляем связи где комнаты ин и аут
	//ft_free_list_down(&map->link_new);
	//map->link_new = ft_copy_list_down(map->link_copy);
	//ft_free_list_down(&map->link_copy);
	ft_free_list_i(&rev_start);
}
