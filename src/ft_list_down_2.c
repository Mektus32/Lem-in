/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aft_list_down_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:42:53 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 21:42:55 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_list_add_back_down_next(t_list_down **a_lst, t_list_i *next)
{
	t_list_down *list;

	if (!a_lst)
		return ;
	list = *a_lst;
	if (*a_lst)
	{
		while (list->down)
			list = list->down;
		list->next = ft_list_copy_i(next);
	}
	else
		return ;
}

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

void		ft_list_add_back_right_down(t_list_down **a_lst, t_list_down *new)
{
	t_list_down	*list;

	list = *a_lst;
	if (*a_lst)
	{
		while (list->right)
			list = list->right;
		list->right = new;
	}
	else
		*a_lst = new;
}

t_list_down	*ft_copy_list_down(t_list_down *head)
{
	t_list_down	*copy;
	t_list_down *one_down;

	copy = NULL;
	if (!head)
		return (NULL);
	while (head)
	{
		one_down =
				ft_list_new_pointer_content_down(ft_list_copy_i(head->next),
						head->content);
		list_add_down(&copy, one_down);
		head = head->down;
	}
	return (copy);
}
