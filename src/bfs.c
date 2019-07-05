#include "lem_in.h"
//-1 если не найдкм ни одного пути
// typedef struct		s_list_i
// {
// 	int			content;
// 	struct s_list_i	*next;
// }					t_list_i;


t_list_i	*ft_lstnew_i(int content)
{
	t_list_i	*list;

	list = NULL;
	list = (t_list_i*)malloc(sizeof(t_list_i));
	if (!list)
		return (NULL);
	if (!content)
	{
		list->content = 0;
	}
	else
	{
		// list->content = malloc(sizeof(int));
		// if (!list->content)
		// 	return (NULL);
		list->content = content;
	}
	list->next = NULL;
	return (list);
}

void	ft_lstaddback_i(t_list_i **alst, t_list_i *new)
{
	t_list_i *list;

	if (!alst)
		return ;
	list = *alst;
	if (*alst)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}

int ft_bfs(t_map *map)
{
	// со старта надо начать просматривать граф
	// если есть ребро, токда присваеваем родителя
	// туда, куда ребро и сохраняем расстояние до starta/
	// путей может быть несколько
	// может ли быть несколько родителей
	// но у нас только матрица и лист
//раньше найти родителей не можем
	int i;
	int j;
	int dist;
	//t_room *room;
	t_room *start;
	t_list_i *vis;

	t_list_i *new;

	i = 0;

	vis = ft_lstnew_i(0);
	start = map->rooms;
	// while (i <= map->c_room)
	// {
	while (vis)
	{
		j = 0;
		while (j <= map->c_room)
		{
			//printf("ii = %d, jj = %d\n", i,j);
			if (map->matr[vis->content][j] == 1)
			{	//надо ли делать граф направленным?
				map->matr[j][vis->content] = 0;
			// 	//комната с индексом j будет иметь родителя i
				new = ft_lstnew_i(j);
				ft_lstaddback_i(&vis, new);
				while (map->rooms && (map->rooms->number != j))
				{
					//printf("i = %d, j = %d, num = %d, %d\n", i, j, map->rooms->number, map->rooms->number == j );

					dist = map->rooms->dist;
					map->rooms = map->rooms->next;
					//break ;
				}
				map->rooms->par_num = i;
				map->rooms->dist = dist + 1;//тк вес ребра = 1 прибавляем его к весу в предыдущей точке
				map->rooms = start;
				
			}
			j++;
		}
		//i++;
		printf("v->n  = %d\n", vis->content);
		vis = vis->next;
		i++;
		
	}
	map->rooms = start;
	return(1);
}