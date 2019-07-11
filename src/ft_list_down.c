// возвращает ссылку на элемент s_list_i
// от номера комнаты

t_list_i *ft_list_i_head(int num, t_list_down **alst)
{
	t_list_down *list;

	if (!alst)
		return (NULL);
	list = *alst;
	while (list)
	{
		if (list->content == num)
		{
			return (list->next);
		}
		list = list->down;
	}
	return (NULL);
}

// создание нового листа
t_list_down	*ft_lstnew_down(int content)
{
	t_list_down	*list;

	list = NULL;
	list = (t_list_down*)malloc(sizeof(t_list_down));
	if (!list)
		return (NULL);
	if (!content)
		list->content = 0;
	else
		list->content = content;
	list->next = NULL;
	list->down = NULL;
	return (list);
}

//добавление вниз нового элемента
/* Функция добавления элемента в конец массива/списка в указатель "down" */
void	ft_lstaddback_down(t_list_down **alst, t_list_down *new)
{
	t_list_down *list;

	if (!alst)
		return ;
	list = *alst;
	if (*alst)
	{
		while (list->down)
			list = list->down;
		list->down = new;
	}
	else
		*alst = new;
}