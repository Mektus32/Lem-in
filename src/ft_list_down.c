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
t_list_down *ft_list_i_head(int num, t_list_down *a_lst)
{
	t_list_down *list;

	if (!a_lst)
		return (NULL);
	list = a_lst;
	while (list)
	{
		if (list->content == num)
			return (list);
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
void	ft_list_add_back_down(t_list_down **a_lst, t_list_down *new)
{
	t_list_down *list;

	if (!a_lst)
		return ;
	list = *a_lst;
	if (*a_lst)
	{
		while (list->down)
			list = list->down;
		list->down = new;
	}
	else
		*a_lst = new;
}
