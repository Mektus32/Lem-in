///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   main.c                                             :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2019/06/30 17:16:18 by ojessi            #+#    #+#             */
///*   Updated: 2019/06/30 17:16:19 by ojessi           ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "lem_in.h"
//
//int 	main(void)
//{
//	ft_printf("check\n");
//	return (0);
//}
//
//t_room	*ft_create_ele(int x, int y, char *name, int number)
//{
//	t_room	*list;
//
//	if (!(list = ft_memalloc(sizeof(t_room))))
//		return (NULL);
//	list->x = x;
//	list->y = y;
//	list->name = name;
//	list->number = number;
//	list->next = NULL;
//	return (list);
//}
//
//t_room	*ft_pushback(t_room **head, t_room *new)
//{
//	if (!head)
//		return (NULL);
//	else if (!*head)
//		*head = new;
//	else
//	{
//		while ((*head)->next)
//			*head = (*head)->next;
//		*head = new;
//	}
//	return (*head);
//}
