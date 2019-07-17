/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:33:12 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/11 17:33:14 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZUALIZER_H
# define VIZUALIZER_H
# define WIDTH 2200
# define HEIGHT 1300
# define BACKGROUND "images/Earth.xpm"
# define ANT "images/littleant2.xpm"
# define ROOMS "images/room_f.xpm"
# define ROOME "images/room_t.xpm"
# define ROOMA "images/room_s.xpm"

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>

typedef	struct		s_coor
{
	int		x;
	int 	y;
	int 	f;
}					t_coor;

typedef	struct		s_turn
{
	char 			**matr;
	struct	s_turn	*next;
	struct	s_turn	*prev;
}					t_turn;

typedef	struct		s_neib
{
	char 	*name;
	struct s_neib	*next;
}					t_neib;

typedef struct		s_room
{
	void			*image;
	char			*name;
	int 			cont;
	int 			x;
	int 			y;
	struct s_room	*down;
	t_neib			*next;
}					t_room;

typedef struct		s_image
{
	void	*img_ant;
	void	*img_background;
	int 	bpp;
	int 	size_line;
	int 	endian;
}					t_image;

typedef struct		s_ob
{
	int 	count_rooms;
	int 	fd;
	void	*mlx_ptr;
	void	*win_ptr;
	int 	ants;
	t_coor	*arr;
	t_room	*rooms;
	t_image	*image;
	t_turn	*turn;
	t_turn	*cur;
}					t_ob;

int					ft_read(t_ob *ob);
void				key_hook(t_ob *ob);
int					ft_read(t_ob *ob);
t_room				*ft_create_room(char *line, int cont, t_ob *ob);
t_room				*ft_push_back_room(t_room **head, t_room *new);
t_neib				*ft_create_neib(char *name);
t_neib				*ft_push_back_neib(t_neib **head, t_neib *new);
t_room				*ft_add_neib(t_room **head, char *line);
t_turn				*ft_create_turn(char *line, t_turn *prev);
t_turn				*ft_push_back_turn(t_turn **head, char *line);
t_turn				*ft_move_turn_next(t_turn *cur, int	step);
t_turn				*ft_move_turn_prev(t_turn *cur, int step);
char 				*ft_super_strrev(char *line);
void				ft_draw(t_ob *ob);
void				ft_draw_rooms(t_ob *ob);
void				ft_room_color(t_room **list, int cont, t_ob *ob);
void 				Brezenhem(int x0, int y0, int x1, int y1, t_ob *ob);//
int					ft_get_y_room(t_room *room, char *name);
int					ft_get_x_room(t_room *room, char *name);
void				ft_draw_turn(t_ob *ob);
int					ft_get_y_room_cont(t_room *room, int cont);
int					ft_get_x_room_cont(t_room *room, int cont);
void				ft_init_arr(t_ob *ob);
int					ft_put_move_ant(int *x0, int *y0, int x1, int y1, int f);
void				ft_draw_menu(t_ob *ob);

#endif
