/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:44:03 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/30 16:44:04 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"

//односвязный список, в таком хранятся комнаты, кротчайший путь, очередь обхода.
typedef struct		s_list_i
{
	int			content;
	struct s_list_i	*next;
}					t_list_i;

//для построение связей между комнатами.
//вниз обход по всем комнатам, в контенте соответсвенно хранится номер комнаты
typedef struct			s_list_down
{
	int					content;
	struct s_list_i		*next; // из каждого столбца в право начинается лист (t_list_i).
	struct s_list_down	*down;
	struct s_list_down	*right; // из каждого столбца в право начинается лист (t_list_down).

}						t_list_down;

//структура каждой комнаты
typedef struct		s_room
{
	int				x;//координаты комнаты
	int				y;
	char			*name;
	int				number;// у первой №0, у последней № c_room
	int 			par_num;
	int 			dist;
	struct s_room	*next;

}					t_room;
//главная структура, которую везде передавать
typedef struct		s_map
{
	int				fd;
	int				c_room;//кол - во комнат
	int 			c_ant;//кол-во муравьев
	t_list_down		*link;//лист - столбец для указания связей
	t_list_down  	*link_new;//новые ссылки после удвление путей
	t_room			*rooms;//лист всех комнат
	t_list_i		*sh;//кротчайший путь // вроде бы можно удалить?!(мы не используем)
	int				len_sh;//длина кратчайшего пути
	t_list_down		*two_path;//
}					t_map;


//map
void				ft_free_map(t_map **map);
	// (valid.c)
// ф., которые проверяют на валидность  - возвращают 1 если все хорошо,
// и 0 еслигде то эрор
//проверяет на валидность первую строку, инициализируя структуру map
int					make_map(int fd, t_map *map);
//проверяет на валидность список комнат, заполняя лист room,
// пока не нашли первую ссылку
int					check_room(t_map *map);

int					created_links(char *line, t_map *map);
//записывает по две связи для каждой комнаты
int					check_links(char *line, t_map *map);

	// (bfs.c)
// 0 - путь не нашли, 1 - есть путь
t_list_i			*ft_bfs(t_map *map);
//помогает найти обратный путь, записывает его в map->sh
t_list_i			*ft_path(t_map *map, int *dist);

	// (ft_bfs_k.c)
t_list_down		*ft_bfs_k(t_map *map, int k);
t_list_i 		*bfs_k_path(t_map *map, t_list_i *cant_go, t_list_down *path_down);
t_list_i	*ft_path_k(t_map *map, int *dist);
int find_room(t_list_i *room, int num);
	// (liba.c)
//ф, которые претендуют на звание стандартных 

int					ft_len_int(int num);
int					ft_max_mass(int *mass); // максимальное в массиве int


	//(list_room.c)
//ф для списка комнат
t_room				*ft_create_ele(char *line, int number);
void				ft_push_back_room(t_room **head, t_room *new);
void				ft_list_add_room(t_room **alst, t_room *new);

	//ft_list_down.c

t_list_down			*ft_list_i_head(int num, t_list_down *alst);
t_list_down			*ft_list_new_down(int content);
void				ft_list_add_back_down(t_list_down **alst, t_list_down *new);
t_list_down			*ft_list_new_pointer_down(t_list_i *next);
void				ft_list_add_back_right_down(t_list_down **alst, t_list_down *new);
int					ft_list_len_down(t_list_down *path);
void				ft_free_first_in_two_path(t_list_down **first);
void				ft_free_list_i(t_list_i **head);
void				ft_free_list_down(t_list_down **head);
t_list_down			*ft_copy_list_down(t_list_down *head);


	// (ft_list_i.c)
//ф для работы с односвязным списком
t_list_i			*ft_list_new_i(int content);
void				ft_list_add_back_i(t_list_i **alst, t_list_i *new);
int					ft_list_len_i(t_list_i *head);
t_list_i			*ft_list_copy_i(t_list_i *head);

void				ft_remove_list_if(t_list_i **head, int content);
void				ft_add_list_if(t_list_i **head, int content, t_list_i *new);
void				ft_list_revers(t_list_i **begin_list);


#endif
