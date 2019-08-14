#include "lem_in.h"


int ft_ant_in_path(int n_ant, int *d, int c_path, int len_max)
{
    int f;//не знаю как избавиться от бесконечного цикла
    int k;

    f = 1;
    while (n_ant > 0 && f)
    {
        k = 0;
        f = 0;// что б знать что мы продолжаем муравьев раскидывать
        while (k < c_path && n_ant)
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
    free(d);
    return (n_ant);
}
int ft_check_path_n(t_list_down *two_path, t_map *map)
{
	t_list_down *path_new;
	int *d;//массив длин путей текущего состояния
	int k;// счетчик массива d
	int n_ant; //временное кол- во муравьев
	int c_path;//кол-во путей
//	int f;//не знаю как избавиться от бесконечного цикла
//	int t1;//время предыдушего пути
	int t_now;
	int len_max;//максимальная длина в массиве

	//t1 = two_path->content;
	path_new = two_path->right;//кол-во путей в новом стостоянии
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
	len_max = ft_max_mass(d, c_path);
	// до равновесия заполним все пути муравьями
    n_ant = ft_ant_in_path(n_ant, d, c_path, len_max);

	//время которое потребуется для прохода этого состояния
	//округляет инт к меньшему значению
	//добавляем 1, если колличество муравьев не 0 осталось
	t_now = len_max + n_ant/c_path + ((n_ant == 0 || (n_ant % c_path == 0)) ? 0 : 1) - c_path;
	if (t_now < two_path->content && map->c_ant >= c_path)//выбираем этот путь
		return (t_now);
	return (0);
}
