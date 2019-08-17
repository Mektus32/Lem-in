/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aft_list_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:39:00 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 21:39:02 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_list_len_down(t_list_down *path)
{
	int	k;

	k = 0;
	while (path->down)
	{
		k++;
		path = path->down;
	}
	return (k);
}

t_list_down	*i_head(int num, t_list_down *a_lst)
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

t_list_down	*list_new_down(int content)
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

void		list_add_down(t_list_down **a_lst, t_list_down *new)
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
