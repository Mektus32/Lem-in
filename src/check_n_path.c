#include "lem_in.h"

int	ft_max_count_path(t_map *map)
{
	int max_count_path;
	int to_end;
	int from_start;
	t_list_i *tmp;

	from_start = 0;
	to_end = 0;
	tmp = ft_list_i_head(0, map->link_new)->next;
	while (tmp)
	{
		from_start++;
		tmp = tmp->next;
	}
	tmp = ft_list_i_head(map->c_room, map->link_new)->next;
	while (tmp)
	{
		to_end++;
		tmp = tmp->next;
	}
	if (from_start > to_end)
		return (to_end);
	else
		return (from_start);
}


int ft_check_path_n(t_list_down *two_path, t_map *map)
{
	t_list_down *path_new;
	int *d;//массив длин путей текущего состояния
	int k;// счетчик массива d
	int n_ant; //временное кол- во муравьев
	int c_path;//кол-во путей
	int f;//не знаю как избавиться от бесконечного цикла
	int t1;//время предыдушего пути
	int t_now;
	int len_max;//максимальная длина в массиве

	t1 = two_path->content;
	//кол-во путей в новом стостоянии
	path_new = two_path->right;
	//path_new->content; пока равен 0, надо перезаписать тужа время
	// - 1 потому что комнату создаем комнату -10
	c_path = ft_list_len_down(path_new) - 1;
	//
	d = (int *)malloc(sizeof(int) * c_path);
	path_new = path_new->down;
	//переходим к 1ому пути в состоянии
	k = 0;
	//заполним длины из структуры
	while (path_new->next)
	{
		d[k++] = path_new->content;
		path_new = path_new->down;
	}
	n_ant = map->c_ant;
	len_max = ft_max_mass(d);
	// до равновесия заполним все пути муравьями
	f = 1;
	while (n_ant > 0 && f)
	{
		k = 0;
		f = 0;// что б знать что мы продолжаем муравьев раскидывать
		while (d[k] && n_ant)
		{
			if (d[k] < len_max)
			{
				d[k] += 1;
				n_ant--;
				f++;
			}
			k++;
		}
	}
	//время которое потребуется для прохода этого состояния
	//округляет инт к меньшему значению
	//добавляем 1, если колличество муравьев не 0 осталось
	t_now = len_max + n_ant/c_path + ((n_ant == 0 || (n_ant % c_path == 0)) ? 0 : 1);
	if (t_now <= t1 && map->c_ant >= c_path)//выбираем этот путь
		return (t_now);
	return (0);
}
