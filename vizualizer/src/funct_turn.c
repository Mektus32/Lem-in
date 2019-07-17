/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 20:05:30 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/15 20:05:32 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

t_turn	*ft_create_turn(char *line, t_turn *prev)
{
	t_turn	*list;

	if (!(list = (t_turn*)malloc(sizeof(t_turn))))
		return (NULL);
	list->matr = ft_strsplit(line, ' ');
	list->next = NULL;
	list->prev = prev;
	return (list);
}

t_turn	*ft_push_back_turn(t_turn **head, char *line)
{
	t_turn	*list;
	t_turn	*tmp;

	if (!head)
		return (NULL);
	list = *head;
	if (list)
	{
		tmp = list;
		while (list->next)
		{
			tmp = list;
			list = list->next;
		}
		list->next = ft_create_turn(line, tmp);
	}
	else
	{
		list = ft_create_turn(line, NULL);
		*head = list;
	}
	return (list);
}

t_turn	*ft_move_turn_next(t_turn *cur, int step)
{
	int		i;

	i = -1;
	while (cur->next && ++i < step)
		cur = cur->next;
	return (cur);
}

t_turn	*ft_move_turn_prev(t_turn *cur, int step)
{
	int		i;

	i = -1;
	while (cur->prev && ++i < step)
		cur = cur->prev;
	return (cur);
}
