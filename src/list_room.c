/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:05:24 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/14 15:05:25 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
// создание элемента списка комнат, на вход получаем строку из консоли
// и порядковый номер комнаты
// в лайне содержится ИМЯ комнаты и ее координаты
// все что до пробела - имя
t_room	*ft_create_ele(char *line, int number)
{
	int i;
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	i = 0;
	while (line[i] != ' ')
		i++;
	room->name = (char*)malloc(sizeof(char) * i + 1);
	room->name[i] = '\0';
	ft_strncpy(room->name, line, i);
	room->x = ft_atoi(line + i + 1);
	room->y = ft_atoi(line + ft_len_int(room->x) + i + 2);
	room->number = number;
	room->next = NULL;
	room->dist = 0;
	free(line);
	return (room);
}
//добавление комнаты в конец списка
void ft_push_back_room(t_room **head, t_room *new)
{
	t_room *list;

	if (!head)
		return ;
	list = *head;
	if (*head)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
}
//добавление комнаты в начало
void	ft_list_add_room(t_room **lst_a, t_room *new)
{
	if (!lst_a)
		return ;
	new->next = *lst_a;
	*lst_a = new;
}

char *ft_name_room(t_room *a_lst, int num)
{
	while (a_lst)
	{
		if (a_lst->number == num)
			return (a_lst->name);
		a_lst = a_lst-> next;
	}
	return (NULL);
}

//есть ли клмната в списке?
int find_room(t_list_i *room, int num)
{
	while (room)
	{
		if (room->content == num)
			return (1);
		room = room->next;
	}
	return (0);
}
