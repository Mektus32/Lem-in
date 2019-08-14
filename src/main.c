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

int is_not_valid(char *line)
{
    ft_printf("%s", line);
    ft_printf("ERROR\n");
    exit(0);
}
/*
 * я решила не делать цикл по гнл, тк это дабавит лишних сравнений после  прохода условий,
 * а количество вызовов ГНЛ не уменьшит
 * */
int valid_map(int fd, t_map *map)
{
    map->rooms = NULL;
    map->link = NULL;
    map->link_copy = NULL;
    map->link_new = NULL;
    map->sh = NULL;
    map->two_path = NULL;
    map->fd = fd;
    map->len_sh = 0;
    map->c_room = 0;
    map->rooms = NULL;
    make_ant(fd, map);
    check_room(map);
    return (1);
}

void	ft_free_map(t_map **map) {
    t_map		*tmp;
    t_list_down *tmp_down;
    int			i;

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
    if (tmp->two_path)
    {
        tmp_down = tmp->two_path->down;
        while (i++ < (*map)->c_path)
            tmp_down = tmp_down->down;
        tmp_down = NULL;
        if (tmp->two_path)
            ft_free_first_in_two_path(&tmp->two_path);
        if (tmp->two_path)
            ft_free_first_in_two_path(&tmp->two_path);
    }
    free(*map);
}

int main(int ac, char	**av)
{
	int		fd;
	t_map	*map;
	char	*str;

	if (ac == 1)
	{
		//fd = /Users/qgilbert/Desktop/lem_in/six/School21-Lem-in/lem-in_test 2/tests/test_5.map
		fd = open("../test", O_RDONLY);
		//fd = 0;
	}
	else
	{
		str = av[1];
		fd = open(str, O_RDONLY);
	}
	map = (t_map*)malloc(sizeof(t_map));
    if (valid_map(fd, map))
	{
		main_path(map);
        ft_printf("\n");
		ant_in_room(map);
	}
	else
		ft_printf("ERROR\n");
	ft_free_map(&map);
	return (0);
}

