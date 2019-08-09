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
typedef struct			s_list_i
{
	int					content;
	struct s_list_i		*next;
}						t_list_i;

//для построение связей между комнатами.
//вниз обход по всем комнатам, в контенте соответсвенно хранится номер комнаты
typedef struct			s_list_down
{
	int					content;
	struct s_list_i		*next; // из каждого столбца в право начинается лист (t_list_i).
	struct s_list_down	*down;
	struct s_list_down	*right; // из каждого столбца в право начинается лист (t_list_down).

}						t_list_down;

typedef struct			s_list_path
{
	int					num_ant;
	char				*name_room;
	struct s_list_path	*next;
	struct s_list_path	*prev; // из каждого столбца в право начинается лист (t_list_down).

}						t_list_path;


//структура каждой комнаты
typedef struct			s_room
{
	int					x;//координаты комнаты
	int					y;
	char				*name;
	int					number;// у первой №0, у последней № c_room
	struct s_room		*next;
	int					dist;
}						t_room;
//главная структура, которую везде передавать
typedef struct		s_map
{
	int				fd;
	int				c_room;//кол - во комнат
	int 			c_ant;//кол-во муравьев
	t_list_down		*link;//лист - столбец для указания связей
	t_list_down  	*link_new;//новые ссылки после удвление путей
	t_list_down		*link_copy;
	t_room			*rooms;//лист всех комнат
	t_list_i		*sh;//кротчайший путь // вроде бы можно удалить?!(мы не используем)
	int				len_sh;//длина кратчайшего пути
	t_list_down		*two_path;//
	int 			c_path;
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
t_list_down			*ft_bfs_k(t_map *map, int k);
t_list_i 			*bfs_k_path(t_map *map, t_list_i *cant_go);
t_list_i			*ft_path_k(t_map *map, int *dist);

	// (liba.c)
//ф, которые претендуют на звание стандартных 

int					ft_len_int(int num);
int					ft_max_mass(int *mass, int k); // максимальное в массиве int
int *make_mass(int k);

	//(list_room.c)
//ф для списка комнат
t_room				*ft_create_ele(char *line, int number);
void				ft_push_back_room(t_room **head, t_room *new);
void				ft_list_add_room(t_room **a_lst, t_room *new);
char 				*ft_name_room(t_room *a_lst, int num);
int 				find_room(t_list_i *room, int num); /* 1 - если комната есть, 0 - иначе*/
	//ft_list_down.c

t_list_down			*ft_list_i_head(int num, t_list_down *a_lst);
t_list_down			*ft_list_new_down(int content);
void				ft_list_add_back_down(t_list_down **a_lst, t_list_down *new);
t_list_down			*ft_list_new_pointer_down(t_list_i *next);
void				ft_list_add_back_right_down(t_list_down **a_lst, t_list_down *new);
t_list_down			*ft_list_new_pointer_content_down(t_list_i *next, int content);
int					ft_list_len_down(t_list_down *path);
void				ft_free_first_in_two_path(t_list_down **first);
void				ft_free_list_i(t_list_i **head);

t_list_down			*ft_copy_list_down(t_list_down *head);
void	ft_list_add_back_down_next(t_list_down **a_lst, t_list_i *new);


	// (ft_list_i.c)
//ф для работы с односвязным списком
void ft_lst_plus_copy(t_list_i **lst_a, t_list_i *new);
void	ft_list_add_back_i_one(t_list_i **lst_a, int content);

t_list_i			*ft_list_new_i(int content);
void	ft_list_add_back_i(t_list_i **lst_a, t_list_i *new);
void ft_list_add_back_i_if_not(t_list_i **lst_a, int content, t_list_i *all_order);

int					ft_list_len_i(t_list_i *head);
t_list_i			*ft_list_copy_i(t_list_i *head);

void				ft_remove_list_if(t_list_i **head, int content);
void				ft_add_list_if(t_list_i **head, int content, t_list_i *new);
void				ft_list_revers(t_list_i **begin_list);

//list_path
t_list_path	*ft_list_new_path(int num_ant, char *name, t_list_path *prev);
t_list_path	*ft_list_add_back_path(t_list_path **head, int num_ant, char *name);
t_list_path *path_n_mass(int c_path);



	//check_n_path.c
int	ft_max_count_path(t_map *map);
int ft_check_path_n(t_list_down *two_path, t_map *map);

//free.c
void 	ft_free_list_i(t_list_i **head);
void	ft_free_list_down(t_list_down **head);
void	ft_free_first_in_two_path(t_list_down **first);
void	ft_free_list_room(t_room **head);
void	ft_free_map(t_map **map);
void free_tmp_path(t_list_path **path_i, int c_path);
// ft_print.c

void ft_print_all_path(t_list_down *path_all);
void	ft_pri(t_map *map);
void	ft_pri_cop(t_map *map);
void	ft_pri_sh(t_map *map);
void pr_list(t_list_i *new);

// suurballe.c
void ft_new_room(t_map *map, t_list_i *sh);
void ft_del_shared_path(t_map *map, t_list_i *sh, t_list_i *rev_2);

// удаляет инверсные пути в link_new
void ft_del_shared_path(t_map *map, t_list_i *sh, t_list_i *rev_2);
	//path.c
void main_path(t_map *map);
void	del_link_path(t_map *map);
t_list_i *one_big_path(t_map *map);

//ant_room
void ant_in_room(t_map *map);
void	ft_pars_ant(t_map *map, t_list_path *paths, int count);
void	ft_move_ant_in_path(t_list_path *path);
int		ft_count_ant(t_list_path *path);

#endif
