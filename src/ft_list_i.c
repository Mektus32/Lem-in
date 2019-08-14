/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:04:21 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/14 15:04:23 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*Создание нового элемента списка*/
t_list_i   *ft_list_new_i(int content)
{
	t_list_i   *list;

	if (!(list = (t_list_i*)malloc(sizeof(t_list_i))))
		return (NULL);
	if (!content)
		list->content = 0;
	else
		list->content = content;
	list->next = NULL;
	return (list);
}

/*Добавление эдемента списка в конец*/
void   ft_list_add_back_i_one(t_list_i **lst_a, int content)
{
	t_list_i *list;

	if (!(lst_a))
		return ;
	list = *lst_a;
	if (*lst_a)
	{
		while (list->next)
			list = list->next;
		list->next = ft_list_new_i(content);
	}
	else
		*lst_a = ft_list_new_i(content);
}
void   ft_list_add_back_i(t_list_i **lst_a, t_list_i *new)
{
	t_list_i *list;

	if (!(lst_a))
		return ;
	list = *lst_a;
	if (!new)
		return ;
	if (*lst_a)
	{
		while (list->next)
			list = list->next;
		list->next = ft_list_new_i(new->content);
		list = list->next;
		new = new->next;
	}
	else
	{
		*(lst_a) = ft_list_new_i(new->content);
		list = (*lst_a)->next;
		new = new->next;
	}
	while (new)
	{
		list->next = ft_list_new_i(new->content);
		list = list->next;
		new = new->next;
	}

}


/* Функция удаления элемента из списка типа t_list_i при равенстве "content" */
void   ft_remove_list_if(t_list_i **head, int content)
{
	t_list_i   *tmp;
	t_list_i   *list;

	if (!head )
		return ;
	if (!*head)
		return ;
	list = *head;
	if (list->content == content)
	{
		list = list->next;
		free(*head);
		*head = (list);
		return ;
	}
	tmp = list;
	while (list)
	{
		if (list->content == content)
		{
			tmp->next = list->next;
			free(list);
			list = tmp;
			return ;
		}
		tmp = list;
		list= list->next;
	}
}


/* Функция разворота списка */
void   ft_list_revers(t_list_i **begin_list)
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
	*begin_list = tmp;
}


