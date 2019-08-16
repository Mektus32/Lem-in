/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avalid_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 21:12:50 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/16 21:12:52 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ф. вызывается для каждой входной строки, где есть - и нет ' '
** заполняет ссылки в две стороны
**если не нашли одну из комнат - возвращает 0
**start = map->rooms; - //находим комнату из строки до '-' во всем списке комнат
**пока не нашли название комнаты которая в лайн переходим по списку комнат
**надо что б len симолов в строке совпадали и комнате, а следующий был '-'
** start - комната до знака '-' => s
** tmp -  комната после '-' => t
** len - длина имени первой комнаты =>l
** f - first
**se - second
*/

int	check_links(char *line, t_map *map)
{
	t_room			*s;
	t_room			*t;
	int				l;
	t_list_down		*f;
	t_list_down		*se;

	s = map->rooms;
	while (s)
	{
		l = ft_strlen(s->name);
		if (ft_strnequ(s->name, line, l) && ft_strnequ("-", line + l, 1))
		{
			t = map->rooms;
			while (t)
			{
				if (ft_strequ(t->name, line + l + 1) && t->number != s->number)
				{
					f = ft_list_i_head(s->number, map->link);
					se = ft_list_i_head(t->number, map->link);
					ft_list_add_back_i_or_exit(&f->next, t->number, f->next);
					ft_list_add_back_i_or_exit(&se->next, s->number, se->next);
					ft_str_print_del(&line);
					return (1);
				}
				t = t->next;
			}
			return (is_not_valid("not room in link\n"));
		}
		s = s->next;
	}
	return (is_not_valid("not room in link\n"));
}

/*
**копирует список комнат в столбец смежности
**по идее список комнат меняться не будет - можно оставить ссылки (?)
**для каждой line, которая не коммент заполняем ссылки
*/

int	created_links(char *line, t_map *map, t_valid *val_id)
{
	t_room	*tmp;

	tmp = map->rooms;
	while (tmp)
	{
		ft_list_add_back_down(&map->link, ft_list_new_down(tmp->number));
		tmp = tmp->next;
	}
	check_links(line, map);
	while ((line = ft_check_cmd(&map->fd)))
	{
		if (line[0] == '#')
			return (is_not_valid("end or start in link\n"));
		check_links(line, map);
	}
	if (!line && val_id->start == 2 && val_id->end == 2)
	{
		free(val_id);
		return (1);
	}
	return (is_not_valid("no start or end\n"));
}
