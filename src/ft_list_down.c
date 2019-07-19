/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:04:50 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/14 15:04:51 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//считаем колличество путей в состоянии
int ft_list_len_down(t_list_down *path)
{
	int k;

	k = 0;
	while(path->down)
	{
		k++;
		path = path->down;
	}
	return (k);
}

// возвращает ссылку на элемент s_list_i
// от номера комнаты

t_list_down *ft_list_i_head(int num, t_list_down *alst)
{
	t_list_down *list;

	if (!alst)
		return (NULL);
	list = alst;
	while (list)
	{
		if (list->content == num)
		{
			return (list);
		}
		list = list->down;
	}
	return (NULL);
}

// создание нового листа
t_list_down	*ft_list_new_down(int content)
{
	t_list_down	*list;

	list = NULL;
	list = (t_list_down*)malloc(sizeof(t_list_down));
	if (!list)
		return (NULL);

	list->content = content;
	list->next = NULL;
	list->down = NULL;
	list->right = NULL;
	return (list);
}

//добавление вниз нового элемента
/* Функция добавления элемента в конец массива/списка в указатель "down" */
void	ft_list_add_back_down(t_list_down **alst, t_list_down *new)
{
	t_list_down *list;

	if (!alst)
		return ;
	list = *alst;
	if (*alst)
	{
		while (list->down)
			list = list->down;
		list->down = new;
	}
	else
		*alst = new;
}

/* Функция добавляения элемента в конец списка и записи туда кратчайшего пути*/
t_list_down	*ft_list_new_pointer_down(t_list_i *next)
{
	t_list_down	*list;

	if (!(list = (t_list_down*)malloc(sizeof(t_list_down))))
		return (NULL);
	list->content = ft_list_len_i(next);
	list->next = next;
	list->down = NULL;
	return (list);
}

//создает даун и в некст записывает лист
t_list_down	*ft_list_new_pointer_content_down(t_list_i *next, int content)
{
	t_list_down	*list;

	if (!(list = (t_list_down*)malloc(sizeof(t_list_down))))
		return (NULL);
	list->content = content;
	list->next = next;
	list->down = NULL;
	return (list);
}

void	ft_list_add_back_right_down(t_list_down **alst, t_list_down *new)
{
	t_list_down	*list;

	if (!(list = (t_list_down*)malloc(sizeof(t_list_down))))
		return ;
	list = *alst;
	if (*alst)
	{
		while (list->right)
			list = list->right;
		list->right = new;
	}
	else
		*alst = new;
}

/* Функция копирования списка down */
t_list_down	*ft_copy_list_down(t_list_down *head)
{
	t_list_down	*copy;

	copy = NULL;
	if (!head)
		return (NULL);
	while (head)
	{
		ft_list_add_back_down(&copy, ft_list_new_pointer_content_down(ft_list_copy_i(head->next), head->content));
		head = head->down;
	}
	return (copy);
}