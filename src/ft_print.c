#include "lem_in.h"

void	ft_pri(t_map *map)
{
	t_list_down	*tmp;
	t_list_i	*right;

	tmp = map->link;
	while (tmp)
	{
		ft_printf("room[%d]->", tmp->content);
		right = tmp->next;
		while (right)
		{
			ft_printf("%d->", right->content);
			right = right->next;
		}
		ft_printf("\n");
		tmp = tmp->down;
	}
}

void	ft_pri_cop(t_map *map)
{
	t_list_down	*tmp;
	t_list_i	*right;
	int 		i;

	i = 0;
	tmp = map->link_new;
	while (tmp)
	{
		ft_printf("room[%d]->", tmp->content);
		right = tmp->next;
		while (right)
		{
			ft_printf("%d->", right->content);
			right = right->next;
//			i++;
//			if (i == 15)
//				return ;
		}
		ft_printf("\n");
		tmp = tmp->down;

	}
}

//принт путь
void	ft_pri_sh(t_map *map)
{
	t_list_i	*sh;

	sh = map->sh;
	ft_printf("sh = ");
	while (sh)
	{
		ft_printf("%d-", sh->content);
		sh = sh->next;
	}
	ft_printf("\n");
}

void pr_list(t_list_i *new)
{
	while (new)
	{
		printf("l_c = %d, ",new->content);
		new = new->next;
	}
	printf("\n");
}
