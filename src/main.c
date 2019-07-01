/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:16:18 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/30 17:16:19 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int main(int ac, char	**av)
{
	int fd;
	t_rlist *rooms;

	rooms = NULL;
	if (ac > 0)
	{
		fd = open(av[1], O_RDONLY);
		printf("st = %d\n", check_room(fd, &rooms));
	}
	while(rooms)
	{
		printf("%p, name = %d\n", rooms, ((rooms->content->x)));
		rooms = rooms->next;
	}
	return (0);
}
