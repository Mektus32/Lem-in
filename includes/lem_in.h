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
	char			*str;
	int				*dist;
}					t_map;
/*
 * существование и хранение первой и последней комнаты
 * 0 - такой коснаты нет
 * 1 - есть такая комната
 * 2 - такая комната заполнена
 * 4 - что -то пошло не так
 * tek_num - текущий номер комнаты
 * */
typedef struct      s_valid
{
    int             start;
    int             end;
    int             tek_num;
}                   t_valid;
/**(main.c)
 * is_not_valid - exit, если не валид
 * valid_map - валидность входных данных, инициализируя структуру map
 */
int     is_not_valid(char *line);
int     valid_map(int fd, t_map *map);
void    ft_free_map(t_map **map);
/**(valid.c)
 * make_ant - проверяет на валидность первую строку
 * check_room - проверяет на валидность список комнат, заполняя лист room,
 * +static is_elem + start_room + end_room
 * (valid_link.c)
 * created_links - создает ссылки(записывает по две связи для каждой комнаты)
 * check_links - оценивает валидность ссылок
 */
int make_ant(t_map *map);
int					check_room(t_map *map);

int					created_links(char *line, t_map *map, t_valid *val_id);
int					check_links(char *line, t_map *map);
/**(path.c)
 * main_path - ищет первый путь, если находит переходик к main_path_2, пока есть выигрыш
 * main_path_2 - ищет заданное кол-во путей
 * del_link_path - удаляет найденный путь в link
 * one_big_path - один большой путь из всех путей состояния
 */
int         main_path(t_map *map);
int         main_path_2(t_map *map,  int k);
void        del_link_path(t_map *map);
t_list_i *one_big_path(t_map *map);
/**(bfs.c)
 * step_1
 * ft_bfs - возвращает один путь
 * ft_path - находит путь по массиву dist
 * ft_bfs_2 - заполняет dist (обход графа)
 */
t_list_i			*ft_bfs(t_map *map);
t_list_i *ft_path(t_map *map);
void ft_bfs_2(t_map *map, t_list_i *order, t_list_i *all_order);
/**(check_n_path.c)
 * ищет выиграш по времени от n путей
 */
int ft_check_path_n(t_list_down *two_path, t_map *map);
int ft_ant_in_path(int n_ant, int *d, int c_path, int len_max);
/**(ft_bfs_k.c)
 * step 3
 * bfs_k_path - ищет путь в новом графе
 * + static int bfs_k_path_2(t_map *map, t_list_i *order, t_list_i *all_order, int *dist)
 * заполняет dist
 * + static t_list_i	*ft_path_k(t_map *map, int *dist)
 * поиск пути по dist
 * step 5
 * ft_bfs_k - ищет к путей в графе без обзих ребер
 * + static  int path_not_in(t_list_i *path_1, t_list_i *path_2)
 */
t_list_i 			*bfs_k_path(t_map *map, t_list_i *cant_go);
t_list_down			*ft_bfs_k(t_map *map, int k);

/**(suurballe.c)
 * step 5
 * ft_del_shared_path - удаляет реверсные рёбра
 * ft_new_room - добавляет новые комнаты
 * + static void ft_new_link_in(t_map *map, t_list_i *sh); - меняет ссылки
 *
 */
void ft_new_room(t_map *map, t_list_i *sh);
void ft_del_shared_path(t_map *map, t_list_i *sh, t_list_i *rev_2);
/**(list_room.c)
 * ф для списка комнат
 * find_room - 1 - если комната есть, 0 - иначе
 */
t_room				*ft_create_ele(char *line, int number);
void				ft_push_back_room(t_room **head, t_room *new);
void				ft_list_add_room(t_room **a_lst, t_room *new);
char 				*ft_name_room(t_room *a_lst, int num);
int 				find_room(t_list_i *room, int num);
/**(list_path.c)
 * ф для массива путей
 * path_n_mass - создает массив на с_path
 * path_add_i - заполнение i-ого элемента массива двухсвязного списка
 */
t_list_path	*ft_list_new_path(int num_ant, char *name, t_list_path *prev);
t_list_path	*ft_list_add_back_path(t_list_path **head, int num_ant, char *name);
t_list_path *path_n_mass(int c_path);
void path_add_i(t_list_path *path_n,  int d_i, t_map *map, t_list_i *tmp_i);
/**(liba.c)
 * ф, которые претендуют на звание стандартных
 * ft_max_mass - максимальное в массиве int
 * ft_str_print_del - печатает т удаляет строку
 * ft_check_cmd - пропускает все коменнты и команды кроме start и end
 */
int					ft_len_int(int num);
int					ft_max_mass(int *mass, int k);
int                 *make_mass(int k);
void                ft_str_print_del(char **as);
char                *ft_check_cmd(int *fd);
/**(ft_list_i.c)
 * ф для работы с односвязным списком
 * ft_list_add_back_i_one - копирует только один элемент в конец
 * ft_list_add_back_i - копирует весь список new в конец
 */
t_list_i			*ft_list_new_i(int content);
void	ft_list_add_back_i_one(t_list_i **lst_a, int content);
void	ft_list_add_back_i(t_list_i **lst_a, t_list_i *new);
void				ft_remove_list_if(t_list_i **head, int content);
void				ft_list_revers(t_list_i **begin_list);
/**(ft_list_i_2.c)
 * ф для работы с односвязным списком
 */
int       ft_list_len_i(t_list_i *head);
t_list_i			*ft_list_copy_i(t_list_i *head);
void ft_list_add_back_i_or_exit(t_list_i **lst_a, int content, t_list_i *all_order);
void ft_list_add_back_i_if_not(t_list_i **lst_a, int content, t_list_i *all_order);
/**(ft_list_down.c)
 * ф для работы с односвязным списком down
 */
int					ft_list_len_down(t_list_down *path);
t_list_down			*ft_list_i_head(int num, t_list_down *a_lst);
t_list_down			*ft_list_new_down(int content);
void				ft_list_add_back_down(t_list_down **a_lst, t_list_down *new);
/**(ft_list_down_2.c)
 * ф для работы с односвязным списком down
 */
void	ft_list_add_back_down_next(t_list_down **a_lst, t_list_i *new);
t_list_down			*ft_list_new_pointer_content_down(t_list_i *next, int content);
void				ft_list_add_back_right_down(t_list_down **a_lst, t_list_down *new);
t_list_down			*ft_copy_list_down(t_list_down *head);
/**(free.c)
 * ф очистки
 */
void free_tmp_path(t_list_path **path_i, int c_path);
void 	ft_free_list_i(t_list_i **head);
void	ft_free_list_down(t_list_down **head);
void				ft_free_first_in_two_path(t_list_down **first);
void	ft_free_list_room(t_room **head);
/**(ant_room.c)

 * ant_in rooom
 * + static void ant_in_path(int *d, t_list_path *tmp_path, t_map *map);
 * (ant_room_2.c)
 */
void ant_in_room(t_map *map);

/** (ant_room_2.c)
 * + static int		ft_count_ant(t_list_path *path);
 * + static int sum_ant(t_list_path **path_a, int c_path)
*/
void	ft_pars_ant(t_map *map, t_list_path **path_a);
void	ft_move_ant_in_path(t_list_path **path_a);
int ft_len_path(t_list_path **path_a, int j);

// ft_print.c
void ft_print_all_path(t_list_down *path_all);
void	ft_pri(t_map *map);
void	ft_pri_cop(t_map *map);
void	ft_pri_sh(t_map *map);
void pr_list(t_list_i *new);

#endif
