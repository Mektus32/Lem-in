/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:08:55 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/08 13:08:56 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* Функции для работы с листами(списками) */

/* Функция удаления элемента из списка типа t_list_i при равенстве "content" */
void	ft_remove_list_if(t_list_i **head, int content)
{
	t_list_i	*tmp;
	t_list_i	*list;

	if (!head )
		return ;
	if (!*head)
		return ;
	list = *head;
	if ((*head)->content == content)
	{
		*head = list->next;
		free(list);
		return ;
	}
	tmp = list;
	while (list)
	{
		if (list->content == content)
		{
			tmp->next = list->next;
			free(list);
			return ;
		}
		tmp = list;
		list= list->next;
	}
}

/* Функция добавления элемента в список типа t_list_i при равенстве "content" */
void	ft_add_list_if(t_list_i **head, int content, t_list_i *new)
{
	if (!head)
		return ;
	if (!*head)
		return ;
	while (*head)
	{
		if ((*head)->content == content)
		{
			(*head)->next = new;
			return ;
		}
		(*head) = (*head)->next;
	}
	free(new);
}

/* Функция вычисления длины списка типа t_list_i */
int 	ft_listlen(t_list_i	*head)
{
	int 	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/* Функция разворота списка */
void	ft_list_revers(t_list_i **begin_list)
{
	t_list_i *list;
	t_list_i *tmp;
	t_list_i *next;

	tmp = 0;
	list = *begin_list;
	while (list)
	{
		next = list->next;
		list->next = tmp;
		tmp = list;
		list = next;
	}
	list = tmp;
}/*Я это взял с бассейна поэтому не уверен что рабоатет,
 * так как тот день у меня не скомпилился из-за .h файла.
 * Проверь по своему(Day11, ex08)*/

/* Функция добавления элемента в конец массива/списка в указатель "io" */
t_list_i	*ft_pushback_io(t_list_i **head, t_list_i *new)
{
	if (!head)
		return (NULL);
	if (!*head)
	{
		*head = new;
		return (NULL);
	}
	while ((*head)->io)
		*head = (*head)->io;
	(*head)->io = new;
}

/* Функция добавления элемента в конец списка в указатель "next" */
void	ft_pushback_i(t_list_i **head, t_list_i *new)
{
	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while ((*head)->next)
		*head = (*head)->next;
	(*head)->next = new;
}

/* Функции для алгоритма */

/* Функция заполнения списка вершин, которые нужно будет разбить */
void	ft_fill_split(t_map *map)
{
	t_list_i	*tmp;

	/* Пройдем все вершины в нашем пути и посчитаем количество соседей у них */

	/* Не берем начало списка (из-за обратной записи пути - это конец пути) */
	tmp = map->sh->next;
	/* Цикл до предпоследнего элемента списка (из-за обратной записи пути последний элемент - это начало пути) */
	while (tmp->next)
	{
		/* Если количество соседей больше одного, то помещаем вершину в список "split" */
		if (ft_listlen(map->matr[tmp->content]) > 1)
		{
			map->split = ft_lstnew_i(tmp->content);
			map->split = map->split->next;
		}
		/* Проходим весь список */
		tmp = tmp->next;
	}
}

/* Функция удаления пути в одном направлении */
void	ft_del_path(t_map *map)
{
	t_list_i	*tmp;

	/* Разворачиваем путь */
	ft_list_revers(&map->sh);
	while (map->sh->next)
	{
		tmp = map->matr[map->sh->content];/* Находим вершину, которая есть в пути */
		ft_remove_list_if(&tmp, map->sh->next->content);/* Удаляем связь между найденой вершиной и следующей вершиной в пути */
		map->sh = map->sh->next;
	}
}

/* Функция разбиения комнат, у которых больше двух связей */
void	ft_breake_room(t_map *map)
{
	t_list_i	*tmp;
	t_list_i	*back;
	int 		i;

	/* Добавление "in и out" в конец массива/списка */
	tmp = map->split;
	while (tmp)
	{
		/* Сначала в конец массива на первой итерации и в конец списка на всех остальных, добавляем сначала in потом out */
		ft_pushback_io(&map->matr[map->c_room], ft_lstnew_i(map->c_room + tmp->content));
		back = ft_pushback_io(&map->matr[map->c_room], ft_lstnew_i(2 * map->c_room + tmp->content));
		/* Добавление в out связи на in */
		ft_add_list_if(&back, 2 * map->c_room + tmp->content, ft_lstnew_i(map->c_room + tmp->content));
		tmp = tmp->next;
	}
	/* Out не получилось связать вообще */
//	/* Добавление связей с out и удаление связей с "целой" комнатой для каждой вершины у которой больше двух соседей */
//	tmp = map->split;
//	while (tmp)
//	{
//		ft_pushback_i(&map->matr[tmp->content], ft_lstnew_i(2 * map->c_room + tmp->content));
//		ft_remove_list_if(&map->matr[tmp->content], tmp->content);
//	}

	/* In получилось засунуть везде где он должен быть, но как сделать из него выход хз, точнее как определить куда выходить
	 * по идее относительно связи, которая участвовала в кратчайшем пути, но это еще как-то найти надо */
	/* Добавление связей с in и удаление связей с "целой" комнатой для каждой вершины у которой больше двух соседей */
	tmp = map->split;
	/* Идем сначала по всем вершинам с большим количеством соседей */
	while (tmp)
	{
		i = 0;
		/* Перебираем все комнаты в списке смежности, чтобы найти где добавить и удалить */
		while (i < map->c_room)
		{
			/* Если найдем комнату, которую надо удалить, то функции по "content" определят надо добавлять/удалять и сделают это */
			ft_add_list_if(&map->matr[i], tmp->content, ft_lstnew_i(map->c_room + tmp->content));
			ft_remove_list_if(&map->matr[i], tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
}


