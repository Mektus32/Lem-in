/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aft_list_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:45:26 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 21:45:33 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list_i		*ft_list_new_i(int content)
{
	t_list_i	*list;

	if (!(list = (t_list_i*)malloc(sizeof(t_list_i))))
		return (NULL);
	if (!content)
		list->cnt = 0;
	else
		list->cnt = content;
	list->next = NULL;
	return (list);
}

void			list_add_i1(t_list_i **lst_a, int content)
{
	t_list_i	*list;

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

void			ft_list_add_back_i(t_list_i **lst_a, t_list_i *new)
{
	t_list_i	*list;

	if (!(lst_a))
		return ;
	list = *lst_a;
	if (!new)
		return ;
	while (list->next)
		list = list->next;
	list->next = ft_list_new_i(new->cnt);
	list = list->next;
	new = new->next;
	while (new)
	{
		list->next = ft_list_new_i(new->cnt);
		list = list->next;
		new = new->next;
	}
}

void			del_lst_if(t_list_i **head, int content)
{
	t_list_i	*tmp;
	t_list_i	*list;

	if (!head || !*head)
		return ;
	list = *head;
	if (list->cnt == content)
	{
		list = list->next;
		free(*head);
		*head = (list);
		return ;
	}
	while (list)
	{
		if (list->cnt == content)
		{
			tmp->next = list->next;
			free(list);
			list = tmp;
			return ;
		}
		tmp = list;
		list = list->next;
	}
}

void			ft_list_revers(t_list_i **begin_list)
{
	t_list_i	*list;
	t_list_i	*tmp;
	t_list_i	*next;

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
