/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asuurballe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:26:03 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/17 16:26:05 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** изменение ссылок
** 1. все комнаты которые ссылались на нашу (АУТ теперь) -
** теперь ссылаются на ИН
** из комнаты аут ссылка теперь только в ИН
** 2. из комнаты больше нет ссылок на АУТ
** итерируемся только по i <= map->c_r
** tek_next - список в котором ищем ссылки на комнату из пути,
** что б поменять их на ин
** СВЯЗИ перезаписываем ЕСЛИ комната не СЛЕД В ПУТИ
** tek_content != sh->next->cnt
*/

static void	ft_new_link_in(t_map *map, t_list_i *sh)
{
	int			i;
	int			tek_content;
	t_list_down	*tek_down;
	t_list_i	*tek_next;

	i = -1;
	tek_down = map->link;
	while (++i <= map->c_r)
	{
		tek_content = tek_down->content;
		tek_next = tek_down->next;
		while (tek_next)
		{
			if (tek_next->cnt == sh->cnt &&
			tek_content != sh->next->cnt)
			{
				list_add_i1(&(i_head(tek_content,
					map->l_new)->next), sh->cnt + map->c_r);
				del_lst_if(&(i_head(tek_content,
					map->l_new)->next), sh->cnt);
			}
			tek_next = tek_next->next;
		}
		tek_down = tek_down->down;
	}
}

/*
** условие замены-удаления: если оставшихся связей больше 1
** добавляет новые комнаты в l_new (ИН комнаты)
** нынешние комнаты в пути заменяем комнатами АУТ
** при обхоже игнорируем комнату end и start (sh = sh->next и while (sh->next))
** r_pred - номер пред. комнаты
** ft_new_link_in - меняет ссылки в l_new
** добавить ИН - комнату в лист линк нью
** в конец исходного СС - нынешнего АУТ добавим ИН
** должны удалить из АУТА в пред комнату на пути - эта связь теперь из ИН
** (след.действие)
** вместо неё должна из нового ин идти в старую комнату(предыдущую) пути
** больше из ИН ничего не выходит
** (для всех комнат, которые ссфлались на текущую - заменить на ссылание в ИН)
** а ссылку на тукущую из комнаты убрать
** ПОКА есть комнаты в СС
** проверяем только связи которые были до добавления новой комнаты
*/

void		ft_new_room(t_map *map, t_list_i *sh)
{
	int	pred;

	pred = sh->cnt;
	sh = sh->next;
	while (sh->next)
	{
		if (ft_list_len_i(i_head(sh->cnt, map->l_new)->next) > 1
		&& sh->cnt != 0 &&
		sh->cnt != map->c_r)
		{
			list_add_down(&map->l_new, list_new_down(sh->cnt + map->c_r));
			list_add_i1(&(i_head(sh->cnt, map->l_new)->next),
						(sh->cnt + map->c_r));
			del_lst_if(&(i_head(sh->cnt, map->l_new)->next), pred);
			list_add_i1(&(i_head(sh->cnt + map->c_r, map->l_new)->next), pred);
			ft_new_link_in(map, sh);
		}
		pred = sh->cnt;
		sh = sh->next;
	}
}

/*
** step 5
** заполняем новый l_new
** удfляет реверсные ребра, но по-моему тут лишний промежкуточный link_copy
** может можно сразу в линк нью записывать
*/

void		ft_del_shared_path(t_map *map, t_list_i *sh, t_list_i *rev_2)
{
	t_list_i	*rev_2c;
	t_list_i	*rev_start;

	ft_free_list_down(&map->l_new);
	map->l_new = ft_copy_list_down(map->link);
	rev_2c = ft_list_copy_i(rev_2);
	ft_list_revers(&rev_2c);
	rev_start = rev_2c;
	while (sh->next)
	{
		rev_2c = rev_start;
		while (rev_2c->next)
		{
			if (sh->cnt == rev_2c->cnt && sh->next->cnt == (rev_2c->next->cnt))
			{
				del_lst_if(&(i_head(sh->cnt, map->l_new)->next), sh->next->cnt);
				del_lst_if(&(i_head(sh->next->cnt, map->l_new)->next), sh->cnt);
			}
			rev_2c = rev_2c->next;
		}
		sh = sh->next;
	}
	ft_free_list_i(&rev_start);
}
