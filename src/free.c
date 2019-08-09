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

void free_tmp_path(t_list_path **path_i, int c_path)
{
	int	i;
	t_list_path *del;
	t_list_path *tmp_i;

	i = 0;
	tmp_i = *(path_i + i);
	while (i < c_path && tmp_i)
	{
		tmp_i = *(path_i + i);
		while (tmp_i)
		{
			del = tmp_i;
			tmp_i = tmp_i->next;
			free(del);
		}
		i++;
	}
}

void 	ft_free_list_i(t_list_i **head)
{
	t_list_i	*list;
	t_list_i	*del;

	if (!head)
		return ;
	if (!*head)
		return ;
	list = *head;
	del = NULL;
	while (list)
	{
		del = list;
		list = list->next;
		if (del)
			free(del);
		del = NULL;
	}
	free(list);
	list = NULL;
	*head = list;
}

void	ft_free_list_down(t_list_down **head)
{
	t_list_down	*del;
	t_list_down	*list;
	t_list_i *del_i;

	if (!head)
		return ;
	if (!*head)
		return ;
	list = *head;

	while (list)
	{
		del = list;
		if (del->next)
		{
			del_i = del->next;
			ft_free_list_i(&del_i);
			del_i = NULL;
		}
		list = list->down;
		free(del);
		del = NULL;
	}
	free(list);
	list = NULL;
	*head = list;
}

void	ft_free_first_in_two_path(t_list_down **first)
{
	t_list_down	*list;
	t_list_down	*del_d;
//	t_list_i *del_n;

	if (!first)
		return ;
	if (!*first)
		return ;
	if (!(*first)->down)
		return ;
	list = (*first);

//	del_n = list->down->next;
//	if (del_n)
//		ft_free_list_i(&del_n);
//	del_n = NULL;
//	while (list)
//	{
		if (list->down)
		{
			del_d = list->down;
			ft_free_list_down(&del_d);
			del_d = NULL;
		}
		else
			del_d = NULL;
//		list = list->down;
//	}
	*first = (*first)->right;
	free(list);

}

//void	ft_free_first_in_two_path(t_list_down **first)
//{
//	t_list_down	*list;
//	t_list_down	*del;
//
//	if (!first)
//		return ;
//	if (!*first)
//		return ;
//	if (!(*first)->down)
//		return ;
//	list = (*first)->down;
//	if (list)
//		ft_free_list_down(&list);
//	free(list);
//	del = *first;
//	*first = (*first)->right;
//	free(del);
//}

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
		del->name = NULL;
		free(del);
		del = NULL;
	}
	*head = NULL;
}

void	ft_free_map(t_map **map) {
	t_map	*tmp;
	t_list_down *tmp_down;
	int		i;

	if (!map)
		return;
	if (!*map)
		return;
	tmp = *map;
	if (tmp->sh)
		ft_free_list_i(&tmp->sh);
	if (tmp->link)
		ft_free_list_down(&tmp->link);
	if (tmp->link_new)
		ft_free_list_down(&tmp->link_new);
	if (tmp->link_copy)
		ft_free_list_down(&tmp->link_copy);
	if (tmp->rooms)
		ft_free_list_room(&tmp->rooms);
	i = 0;
	tmp_down = tmp->two_path->down;
	while (i++ < (*map)->c_path)
		tmp_down = tmp_down->down;
	tmp_down = NULL;
	if (tmp->two_path)
		ft_free_first_in_two_path(&tmp->two_path);
	if (tmp->two_path)
		ft_free_first_in_two_path(&tmp->two_path);
	free(*map);
}
