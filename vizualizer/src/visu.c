/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:32:12 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/15 21:20:03 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void	ft_print_list(t_ob *ob)
{
	t_room	*room;
	t_neib	*neib;
	t_turn	*turn;

	room = ob->rooms;
	while (room)
	{
		printf("room[%s, %d]->", room->name, room->cont);
		neib = room->next;
		while (neib)
		{
			printf("%s->", neib->name);
			neib = neib->next;
		}
		printf("\n");
		room = room->down;
	}
	printf("\n\n");
	turn = ob->turn;
	while (turn)
	{
		printf("%s\n", turn->str);
		turn = turn->next;
	}
}

int 	main(void)
{
	t_ob	*ob;

	ob = ft_memalloc(sizeof(t_ob));
	ob->fd = open("/Users/ojessi/Desktop/lem/vizualizer/out_put", O_RDONLY);
	ob->mlx_ptr = mlx_init();
	ob->win_ptr = mlx_new_window(ob->mlx_ptr, WIDTH, HEIGHT, "Best Lem-in");
	ob->image = (t_image*)malloc(sizeof(t_image));
	if (ft_read(ob))
		return (0);
	ft_print_list(ob);
	ft_draw(ob);
	return (0);
//	char	*line;
//
//	line = (char*)malloc(sizeof(char) * 10);
//	line = (char*)malloc(sizeof(char) * 20);
//	return (0);
}

//int 	main(void)
//{
//	t_ob	*ob;
//	int 	height = HEIGHT;
//	int 	width = WIDTH;
//
//	ob = ft_memalloc(sizeof(t_ob));
//	ob->mlx_ptr = mlx_init();
//	ob->win_ptr = mlx_new_window(ob->mlx_ptr, WIDTH, HEIGHT, "Vizualizer");
//	ob->image = ft_memalloc(sizeof(t_image));
//	ob->image->img_ptr = mlx_new_image(ob->mlx_ptr, WIDTH, HEIGHT);
//	ob->image->img_ant = mlx_xpm_file_to_image(ob->mlx_ptr, BACKGROUND, &width, &height);
//	mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_ant, 0, 0);
//	printf("%p\n", ob->image->img_ant);
//	ob->image->img_ant = mlx_xpm_file_to_image(ob->mlx_ptr, ROOM, &width, &height);
//	for (int i = 0; i < 15; i++)
//		for (int j = 0; j < 15; j++)
//			mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_ant, i * 100 + 50, j * 100 + 50);
//	ob->image->img_ant = mlx_xpm_file_to_image(ob->mlx_ptr, ANT, &width, &height);
//	for (int i = 0; i < 15; i++)
//		for (int j = 0; j < 15; j++)
//			mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_ant, i * 100 + 50, j * 100 + 50);
//
//	key_hook(ob);
//	mlx_loop(ob->mlx_ptr);
//	return (0);
//}
