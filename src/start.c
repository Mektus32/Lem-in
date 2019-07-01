/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:00:58 by qgilbert          #+#    #+#             */
/*   Updated: 2019/07/01 19:00:59 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include "libft.h"

void	ft_lstadd_r(t_rlist **alst, t_rlist *new)
{
	if (!alst)
		return ;
	new->next = *alst;
	*alst = new;
}

t_rlist	*ft_lstnew_r(t_room *content, size_t content_size)
{
	t_rlist	*list;

	list = NULL;
	list = (t_rlist*)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		list->content = (void*)malloc(content_size);
		if (!list->content)
			return (NULL);
		list->content = content;
		list->content_size = content_size;
	}
	list->next = NULL;
	return (list);
}

void	ft_lstaddback_r(t_rlist **alst, t_rlist *new)
{
	t_rlist *list;

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

int		ft_len_int(int num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}


//ретернуть будем статус

t_room *make_room(char *line)
{
	int i;
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	i = 0;
	while (line[i] != ' ')
		i++;
	room->name = (char*)malloc(sizeof(char) * i + 1);
	room->name[i] = '\0';
	room->name = ft_strncpy(room->name, line, i);
	room->x = ft_atoi(line + i);
	room->y = ft_atoi(line + ft_len_int(room->x) + i);
	free(line);
	return (room);

}

int check_links(char *line, int fd)
{
	(void)fd;
	free(line);
	return(1);
}

int	check_room(int fd, t_rlist **rooms)
{
	char *line;
	int status;
	t_room *one_room;
	t_room *last_room;
	t_room *room;
	t_rlist *new;

	status = 0;
	room = NULL;
	one_room = NULL;
	last_room = NULL;
	while (get_next_line(fd, &line) && ft_strlen(line) > 3)
	{
		
		if (ft_strstr(line, "#"))
		{
			if (ft_strstr(line, "##start"))
			{
				free(line);
				get_next_line(fd, &line);
				one_room = make_room(line);
			}
			else if (ft_strstr(line, "##end"))
			{
				free(line);
				get_next_line(fd, &line);
				last_room = make_room(line);
			}
			else
				free(line);
		}
		else if (ft_strstr(line, "-"))
			status = check_links(line, fd);
		else
		{
			room = make_room(line);
			//printf("room = %s\n", room->name);	
			new = ft_lstnew_r(room, sizeof(t_room));
			ft_lstadd_r(rooms, new);
		}
	}
	if (one_room)
	{
		new = ft_lstnew_r(one_room, sizeof(t_room));
		ft_lstadd_r(rooms, new);
	}
	else
		return (-1);
	if (last_room)
	{
		new = ft_lstnew_r(last_room, sizeof(t_room));
		ft_lstaddback_r(rooms, new);	
	}
	else
		return (-1);
	return(status);
}



