#include "lem_in.h"
//Создание нового элемента списка
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
		list->content = content;
	}
	list->next = NULL;
	return (list);
}

//Добавление эдемента списка в конец
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

/* Функция удаления элемента из списка типа t_list_i при равенстве "content" */
void	ft_remove_list_if(t_list_i **head, int content)
{
	t_list_i	*tmp;
	t_list_i	*list;

	if (!head )
		return ;
	if (!*head)
		return ;
	list = *head;
	if (list->content == content)
	{
		list = list->next;
		free(*head);
		*head = (list);
		return ;
	}
	tmp = list;
	while (list)
	{
		if (list->content == content)
		{
			tmp->next = list->next;
			free(list);
			return ;
		}
		tmp = list;
		list= list->next;
	}
}



/* Функция добавления элемента в список типа t_list_i при равенстве "content" */
void	ft_add_list_if(t_list_i **head, int content, t_list_i *new)
{
	if (!head)
		return ;
	if (!*head)
		return ;
	while (*head)
	{
		if ((*head)->content == content)
		{
			(*head)->next = new;
			return ;
		}
		(*head) = (*head)->next;
	}
	free(new);
}
///* Функция добавления элемента в список типа t_list_i при равенстве "content" */
//void	ft_add_list_if(t_list_i **head, int content, t_list_i *new)
//{
//	if (!head)
//		return ;
//	if (!*head)
//		return ;
//	while (*head)
//	{
//		if ((*head)->content == content)
//		{
//			(*head)->next = new;
//			return ;
//		}
//		(*head) = (*head)->next;
//	}
//	free(new);
//}

/* Функция разворота списка */
void	ft_list_revers(t_list_i **begin_list)
{
	t_list_i *list;
	t_list_i *tmp;
	t_list_i *next;

	tmp = 0;
	list = *begin_list;
	while (list)
	{
		next = list->next;
		list->next = tmp;
		tmp = list;
		list = next;
	}
	*begin_list = tmp;
}

/* Функция вычисления длины списка */
int		ft_listlen_i(t_list_i	*head)
{
	int 	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
/*Я это взял с бассейна поэтому не уверен что рабоатет,
 * так как тот день у меня не скомпилился из-за .h файла.
 * Проверь по своему(Day11, ex08)*/

