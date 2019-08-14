/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aft_list_i_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:57:16 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 21:57:17 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_list_len_i(t_list_i *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

t_list_i	*ft_list_copy_i(t_list_i *head)
{
	t_list_i	*copy;

	copy = NULL;
	if (!head)
		return (NULL);
	copy = ft_list_new_i(head->content);
	if (head->next)
	{
		head = head->next;
		ft_list_add_back_i(&copy, head);
	}
	return (copy);
}

void		ft_list_add_back_i_or_exit(t_list_i **lst_a,
		int content, t_list_i *all_order)
{
	t_list_i	*tmp_lst;

	tmp_lst = all_order;
	while (tmp_lst)
	{
		if (tmp_lst->content == content)
			is_not_valid("link alredy exist");
		tmp_lst = tmp_lst->next;
	}
	ft_list_add_back_i_one(lst_a, content);
}

void		ft_list_add_back_i_if_not(t_list_i **lst_a,
		int content, t_list_i *all_order)
{
	t_list_i	*tmp_lst;

	tmp_lst = all_order;
	while (tmp_lst)
	{
		if (tmp_lst->content == content)
			return ;
		tmp_lst = tmp_lst->next;
	}
	ft_list_add_back_i_one(lst_a, content);
}
