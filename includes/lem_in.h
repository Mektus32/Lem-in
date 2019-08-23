/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:44:03 by ojessi            #+#    #+#             */
/*   Updated: 2019/08/14 19:32:50 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

/*
** односвязный список, в таком хранятся комнаты,
** кротчайший путь, очередь обхода.
*/

typedef struct			s_list_i
{
	int					cnt;
	struct s_list_i		*next;
}						t_list_i;

/*
** для построение связей между комнатами.
** вниз обход по всем комнатам, в контенте соответсвенно хранится номер комнаты
** next - из каждого столбца в право начинается лист (t_list_i).
** right - из каждого столбца в право начинается лист (t_list_down).
*/

typedef struct			s_list_down
{
	int					content;
	struct s_list_i		*next;
	struct s_list_down	*down;
	struct s_list_down	*right;

}						t_list_down;

typedef struct			s_list_path
{
	int					num_ant;
	char				*name_room;
	struct s_list_path	*next;
	struct s_list_path	*prev;
}						t_list_path;

/*
** структура каждой комнаты
** у первой №0, у последней № c_r
*/

typedef struct			s_room
{
	int					x;
	int					y;
	char				*name;
	int					number;
	struct s_room		*next;
}						t_room;

/*
** c_r - кол - во комнат
** link - лист - столбец для указания связей
** l_new - новые ссылки после удвление путей
** rooms - лист всех комнат
** sh - кротчайший путь потом меняется
** len_sh - длина кратчайшего пути
*/

typedef struct			s_map
{
	int					fd;
	int					c_r;
	int					c_ant;
	t_list_down			*link;
	t_list_down			*l_new;
	t_room				*rooms;
	t_list_i			*sh;
	int					len_sh;
	t_list_down			*two_path;
	int					c_path;
	char				*str;
	int					*dist;
	int					m;
}						t_map;

/*
** существование и хранение первой и последней комнаты
** 0 - такой коснаты нет
** 1 - есть такая комната
** 2 - такая комната заполнена
** 4 - что -то пошло не так
** tek_num - текущий номер комнаты
*/

typedef struct			s_valid
{
	int					start;
	int					end;
	int					tek_num;
}						t_valid;

/*
** (main.c)
** is_not_valid - exit, если не валид
** valid_map - валидность входных данных, инициализируя структуру map
*/
t_list_down				*ft_bfs_k_new(t_map *map, int k);
int						is_not_valid(char *line);
int						valid_map(int fd, t_map *map);
void					ft_free_map(t_map **map);

/*
** (valid.c)
** make_ant - проверяет на валидность первую строку
** check_room - проверяет на валидность список комнат, заполняя лист room,
** +static is_elem + start_room + end_room
** (valid_link.c)
** created_links - создает ссылки(записывает по две связи для каждой комнаты)
** check_links - оценивает валидность ссылок
*/

int						make_ant(t_map *map);
int						check_room(t_map *map, t_room *last_room);
int						created_links(char *line, t_map *map, t_valid *val_id);
int						check_links(char *line, t_map *map);
t_valid					*ft_create_val(void);

/*
**(path.c)
** main_path - ищет первый путь,
** если находит переходик к main_path_2, пока есть выигрыш
** main_path_2 - ищет заданное кол-во путей
** del_link_path - удаляет найденный путь в link
** one_big_path - один большой путь из всех путей состояния
*/

int						main_path(t_map *map);
int						main_path_2(t_map *map, int k, int n, int win);
void					del_link_path(t_map *map, int n);
t_list_i				*one_big_path(t_map *map, int n);

/*
** (bfs.c)
** step_1
** ft_bfs - возвращает один путь
** ft_path - находит путь по массиву dist
** ft_bfs_2 - заполняет dist (обход графа)
*/

t_list_i				*ft_bfs(t_map *map);
t_list_i				*ft_path(t_map *map);
void					ft_bfs_2(t_map *map, t_list_i *order,
							t_list_i *all_order);

/*
** (check_n_path.c)
** ищет выиграш по времени от n путей
*/

int						ft_check_path_n(t_list_down *two_path,
							t_map *map, int n);
int						ft_ant_in_path(int n_ant, int c_path,
							int len_max, t_map *map);

/*
** (ft_bfs_k.c)
** step 3
** bfs_k_path - ищет путь в новом графе
** + static int bfs_k_path_2(t_map *map,
** t_list_i *order, t_list_i *all_order, int *dist)
** заполняет dist
** + static t_list_i	*ft_path_k(t_map *map, int *dist)
** поиск пути по dist
** step 5
** ft_bfs_k - ищет к путей в графе без обзих ребер
** + static  int path_not_in(t_list_i *path_1, t_list_i *path_2)
*/

t_list_i				*bfs_k_path(t_map *map, t_list_i *cant_go);
t_list_down				*ft_bfs_k(t_map *map, int k);

/*
**(suurballe.c)
** step 5
** ft_del_shared_path - удаляет реверсные рёбра
** ft_new_room - добавляет новые комнаты
** + static void ft_new_link_in(t_map *map, t_list_i *sh); - меняет ссылки
*/

void					ft_new_room(t_map *map, t_list_i *sh);
void					ft_del_shared_path(t_map *map, t_list_i *sh,
							t_list_i *rev_2);

/*
 **(list_room.c)
** ф для списка комнат
** find_room - 1 - если комната есть, 0 - иначе
*/

t_room					*ft_create_ele(char *line, int number);
void					ft_push_back_room(t_room **head, t_room *new);
void					ft_list_add_room(t_room **a_lst, t_room *new);
char					*ft_name_room(t_room *a_lst, int num);
int						find_room(t_list_i *room, int num);

/*
**(list_path.c)
** ф для массива путей
** path_n_mass - создает массив на с_path
** path_add_i - заполнение i-ого элемента массива двухсвязного списка
*/

t_list_path				*ft_list_new_path(int num_ant, char *name,
							t_list_path *prev);
t_list_path				*ft_list_add_back_path(t_list_path **head,
							int num_ant, char *name);
t_list_path				*path_n_mass(int c_path);
void					path_add_i(t_list_path *path_n, int d_i,
							t_map *map, t_list_i *tmp_i);

/*
**(liba.c)
** ф, которые претендуют на звание стандартных
** ft_max_mass - максимальное в массиве int
** ft_str_print_del - печатает т удаляет строку
** ft_check_cmd - пропускает все коменнты и команды кроме start и end
*/

int						ft_len_int(int num);
int						ft_max_mass(int *mass, int k);
int						*make_mass(int k);
void					ft_str_print_del(char **as);
char					*ft_check_cmd(int *fd);
int						*make_mass_cant_go(t_map *map, t_list_i *cant_go);

/*
**(ft_list_i.c)
** ф для работы с односвязным списком
** ft_list_add_back_i_one - копирует только один элемент в конец
** ft_list_add_back_i - копирует весь список new в конец
*/

t_list_i				*ft_list_new_i(int content);
void					list_add_i1(t_list_i **lst_a, int content);
void					ft_list_add_back_i(t_list_i **lst_a, t_list_i *new);
void					del_lst_if(t_list_i **head, int content);
void					ft_list_revers(t_list_i **begin_list);

/*
**(ft_list_i_2.c)
** ф для работы с односвязным списком
*/

int						ft_list_len_i(t_list_i *head);
t_list_i				*ft_list_copy_i(t_list_i *head);
void					ft_list_add_back_i_or_exit(t_list_i **lst_a,
							int content, t_list_i *all_order);
void					ft_list_add_back_i_if_not(t_list_i **lst_a,
							int content, t_list_i *all_order);

/*
**(ft_list_down.c)
** ф для работы с односвязным списком down
**ft_list_len_down - считаем колличество путей в состоянии
**ft_list_i_head - возвращает ссылку на элемент s_list_iот номера комнаты
*/

int						ft_list_len_down(t_list_down *path);
t_list_down				*i_head(int num, t_list_down *a_lst);
t_list_down				*list_new_down(int content);
void					list_add_down(t_list_down **a_lst, t_list_down *new);

/*
**(ft_list_down_2.c)
** ф для работы с односвязным списком down
*/

void					ft_list_add_back_down_next(t_list_down **a_lst,
							t_list_i *new);
t_list_down				*ft_list_new_pointer_content_down(t_list_i *next,
							int content);
void					ft_list_add_back_right_down(t_list_down **a_lst,
							t_list_down *new);
t_list_down				*ft_copy_list_down(t_list_down *head);

/*
**(free.c)
** ф очистки
*/

void					free_tmp_path(t_list_path **path_i, int c_path);
void					ft_free_list_i(t_list_i **head);
void					ft_free_list_down(t_list_down **head);
void					ft_free_first_in_two_path(t_list_down **first);
void					ft_free_list_room(t_room **head);

/*
** (ant_room.c)
** ant_in rooom
** + static void ant_in_path(int *d, t_list_path *tmp_path, t_map *map);
*/

void					ant_in_room(t_map *map);

/*
** (ant_room_2.c)
** + static int		ft_count_ant(t_list_path *path);
** + static int sum_ant(t_list_path **path_a, int c_path)
*/

int						ft_count_ant(t_list_path *path);
int						sum_ant(t_list_path **path_a, int c_path);
void					ft_pars_ant(t_map *map, t_list_path **path_a);
void					ft_move_ant_in_path(t_list_path **path_a);
int						ft_len_path(t_list_path **path_a, int j);

/*
**void					ft_print_all_path(t_list_down *path_all);
**void					ft_pri(t_map *map);
**void					ft_pri_cop(t_map *map);
**void					ft_pri_sh(t_map *map);
**void					pr_list(t_list_i *new);
*/

#endif
