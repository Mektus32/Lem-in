/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:24:01 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/15 15:24:02 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"
#define ABS(Value) (Value < 0 ? -(Value) : Value)

t_room	*ft_create_room(char *line, int cont, t_ob *ob)
{
	t_room	*list;
	int		i;

	if (!(list = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	list->down = NULL;
	list->next = NULL;
	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	list->name = ft_strsub(line, 0, i);
	i++;
	list->x = ABS((ft_atoi(line + i) * 3)) % 2100 + 150;
	while (ft_isdigit(line[i]))
		i++;
	i++;
	list->y = ABS((ft_atoi(line + i) * 3)) % 1200 + 150;
	list->cont = cont;
	ft_room_color(&list, cont, ob);
	free(line);
	return (list);
}

t_room	*ft_push_back_room(t_room **head, t_room *new)
{
	t_room	*list;

	if (!head)
		return (NULL);
	list = *head;
	if (list)
	{
		while (list->down)
		{
			if (!ft_strcmp(list->name, new->name))
				return (list);
			list = list->down;
		}
		list->down = new;
	}
	else
	{
		list = new;
		*head = list;
	}
	return (list);
}

t_neib	*ft_create_neib(char *name)
{
	t_neib	*list;

	if (!(list = (t_neib*)malloc(sizeof(t_neib))))
		return (NULL);
	list->name = name;
	list->next = NULL;
	return (list);
}

t_neib	*ft_push_back_neib(t_neib **head, t_neib *new)
{
	t_neib	*list;

	if (!head)
		return (NULL);
	list = *head;
	if (list)
	{
		while (list->next)
		{
			if (!ft_strcmp(list->name, new->name))
				return (list);
			list = list->next;
		}
		list->next = new;
	}
	else
	{
		list = new;
		*head = list;
	}
	return (list);
}

t_room	*ft_add_neib(t_room **head, char *line)
{
	int		i;
	t_room	*list;

	if (!head || !*head)
		return (0);
	i = 0;
	while (line[i] != '\0' && line[i] != '-')
		i++;
	list = *head;
	while (list)
	{
		if (!ft_strncmp(list->name, line, i))
		{
			ft_push_back_neib(&list->next,
					ft_create_neib(ft_strdup(line + i + 1)));
			return (list);
		}
		list = list->down;
	}
	return (NULL);
}
