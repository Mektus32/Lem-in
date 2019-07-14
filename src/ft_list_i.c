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

//Создание нового элемента списка
t_list_i	*ft_list_new_i(int content)
{
	t_list_i	*list;

	list = NULL;
	list = (t_list_i*)malloc(sizeof(t_list_i));
	if (!list)
		return (NULL);
	if (!content)
	{
		list->content = 0;
	}
	else
	{
		list->content = content;
	}
	list->next = NULL;
	return (list);
}

//Добавление эдемента списка в конец
void	ft_list_add_back_i(t_list_i **alst, t_list_i *new)
{
	t_list_i *list;

	if (!alst)
		return ;
	list = *alst;
	if (*alst)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}

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
	*begin_list = tmp;
}

/* Функция вычисления длины списка */
int		ft_list_len_i(t_list_i *head)
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

/* Функция копирования списка i */
t_list_i	*ft_list_copy_i(t_list_i *head)
{
	t_list_i	*copy;

	copy = NULL;
	if (!head)
		return (NULL);
	while (head)
	{
		ft_list_add_back_i(&copy, ft_list_new_i(head->content));
		head = head->next;
	}
	return (copy);
}