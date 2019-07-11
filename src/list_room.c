#include "lem_in.h"
// создание элемента списка комнат, на вход получаем строку из консоли
// и порядковый номер комнаты
// в лайне содержится ИМЯ комнаты и ее координаты
// все что до пробела - имя
t_room	*ft_create_ele(char *line, int number)
{
	int i;
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	i = 0;
	while (line[i] != ' ')
		i++;
	room->name = (char*)malloc(sizeof(char) * i + 1);
	room->name[i] = '\0';
	ft_strncpy(room->name, line, i);
	room->x = ft_atoi(line + i + 1);
	room->y = ft_atoi(line + ft_len_int(room->x) + i + 2);
	room->number = number;
	room->next = NULL;
	room->dist = 0;
	free(line);
	return (room);
}
//добавление комнаты в конец списка
void ft_pushback(t_room **head, t_room *new)
{
	t_room *list;

	if (!head)
		return ;
	list = *head;
	if (*head)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
}
//добавление комнаты в начало
void	ft_lstadd_r(t_room **alst, t_room *new)
{
	if (!alst)
		return ;
	new->next = *alst;
	*alst = new;
}