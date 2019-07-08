/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:59:32 by ojessi            #+#    #+#             */
/*   Updated: 2019/04/18 21:17:28 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_free_joint(char *new, char *src)
{
	char		*tmp;

	if (!(tmp = ft_strjoin(new, src)))
		return (NULL);
	free(new);
	new = NULL;
	return (tmp);
}

static	char	*ft_del(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if ((str[i] && !str[i + 1]) || !str[i])
	{
		ft_strdel(&str);
		return (NULL);
	}
	new = ft_strdup(str + i + 1);
	ft_strdel(&str);
	return (new);
}

static	char	*ft_fill_line(char **str)
{
	int			i;
	int			len;
	char		*new;

	i = 0;
	len = 0;
	while ((*str)[i])
	{
		i++;
		len++;
	}
	new = (char*)malloc(sizeof(char) * len + 1);
	i = 0;
	while ((*str)[i] != '\n' && i < len)
	{
		new[i] = (*str)[i];
		i++;
	}
	*str = ft_del(*str);
	new[i] = '\0';
	return (new);
}

static	t_list	*ft_return_list(t_list **begin_list, int fd,
									char **line)
{
	t_list		*list;
	t_list		*cur;

	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (NULL);
	list = *begin_list;
	if (!(cur = ft_list_foreach_if(list, fd)))
		if (!(cur = ft_list_push_back(&list, NULL, fd)))
			return (NULL);
	if (!cur->content)
		cur->content = ft_strnew(1);
	return (cur);
}

int				get_next_line(const int fd, char **line)
{
	static	t_list	*list = NULL;
	int				ret;
	char			buf[BUFF_SIZE + 1];
	t_list			*cur;

	if (!list)
		list = ft_list_add(NULL, fd);
	if (!(cur = ft_return_list(&list, fd, line)))
		return (-1);
	while (!(ft_strchr(cur->content, '\n')))
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[ret] = '\0';
		cur->content = ft_free_joint(cur->content, buf);
		if (ret == 0 && *((char*)cur->content) == '\0')
		{
			ft_list_remove_free_if(&list, fd);
			return (0);
		}
		if (ret == 0)
			break ;
	}
	*line = ft_fill_line((char**)(&(cur->content)));
	return (1);
}
