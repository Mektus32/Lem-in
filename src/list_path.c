#include "lem_in.h"

t_list_path	*ft_list_new_path(int num_ant, char *name, t_list_path *prev)
{
	t_list_path	*list;

	if (!(list = (t_list_path*)malloc(sizeof(t_list_path))))
		return (NULL);
	list->num_ant = num_ant;
	list->name_room = name;
	list->next = NULL;
	list->prev = prev;
	//free(line);
	return (list);
}

t_list_path	*ft_list_add_back_path(t_list_path **head, int num_ant, char *name)
{
	t_list_path	*list;
	t_list_path	*tmp;

	if (!head)
		return (NULL);
	list = *head;
	if (list)
	{
		tmp = NULL;
		while (list && list->next)
		{
			tmp = list;
			list = list->next;
		}
		if (tmp && tmp->next)
			list->next = ft_list_new_path(num_ant, name, tmp->next);
		else
			list->next = ft_list_new_path(num_ant, name, NULL);

	}
	else
	{
		list = ft_list_new_path(num_ant, name, NULL);
		*head = list;
	}
	return (list);
}

/*
 * массив из n путей
 * */
t_list_path *path_n_mass(int c_path)
{
	t_list_path *tmp_path;
	t_list_path *tmp_null;
	int i;

	tmp_path = (t_list_path*)malloc(sizeof(t_list_path) * (c_path + 1));
	i = 0;
	while (i < c_path)
	{
		tmp_path[i].name_room = 0;
		tmp_path[i].next = NULL;
		tmp_path[i].num_ant = 0;
		tmp_path[i].prev = NULL;
		i++;
	}
	tmp_null = (tmp_path + i);
	tmp_null = NULL;
	return (tmp_path);

}