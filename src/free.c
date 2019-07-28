/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:07:00 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/14 14:07:02 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	ft_free_list_i(t_list_i **head)
{
	t_list_i	*list;
	t_list_i	*del;

	if (!head)
		return ;
	if (!*head)
		return ;
	list = *head;
	while (list)
	{
		del = list;
		list = list->next;
		free(del);
		del = NULL;
	}
	*head = NULL;
}

void	ft_free_list_down(t_list_down **head)
{
	t_list_down	*del;
	t_list_down	*list;

	if (!head)
		return ;
	if (!*head)
		return ;
	list = *head;
	while (list)
	{
		del = list;
		list = list->down;
		ft_free_list_i(&del->next);
		free(del);
		del = NULL;
	}
	*head = NULL;
}

void	ft_free_first_in_two_path(t_list_down **first)
{
	t_list_down	*list;
	t_list_down	*del;

	if (!first)
		return ;
	if (!*first)
		return ;
	if (!(*first)->down)
		return ;
	list = (*first)->down;
	//ft_free_list_down(&list);
	free(list);
	del = *first;
	*first = (*first)->right;
	free(del);
}

void	ft_free_list_room(t_room **head)
{
	t_room	*list;
	t_room	*del;

	if (!head)
		return ;
	if (!*head)
		return ;
	list = *head;
	while (list)
	{
		del = list;
		list = list->next;
		free(del->name);
		free(del);
	}
	*head = NULL;
}

void	ft_free_map(t_map **map)
{
	t_map	*tmp;

	if (!map)
		return ;
	if (!*map)
		return ;
	tmp = *map;
	ft_free_list_down(&tmp->link);
	ft_free_list_room(&tmp->rooms);
	ft_free_first_in_two_path(&tmp->two_path);
	ft_free_first_in_two_path(&tmp->two_path);
	free(*map);
	*map = NULL;
}