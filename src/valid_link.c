#include "lem_in.h"

/*
*ф. вызывается для каждой входной строки, где есть - и нет ' '
*заполняет ссылки в две стороны
*если не нашли одну из комнат - возвращает 0
*start = map->rooms; - //находим комнату из строки до '-' во всем списке комнат
*/
int check_links(char *line, t_map *map)
{
    t_room			*start; // комната до знака '-'
    t_room			*tmp; // комната после '-'
    int				len; // длина имени первой комнаты
    t_list_down		*first;
    t_list_down		*second;

    start = map->rooms;
    while (start)
    {
        len = ft_strlen(start->name);
        //пока не нашли название комнаты которая в лайн переходим по списку комнат
        // надо что б len симолов в строке совпадали и комнате, а следующий был '-'
        if (ft_strnequ(start->name, line, len) && ft_strnequ("-", line + len, 1))
        {
            //комнату до '-' нашли, ищем ту что после '-', начиная с начала списка комнат
            tmp = map->rooms;
            while (tmp)
            {
                if (ft_strequ(tmp->name, line + len + 1) && tmp->number != start->number)
                {
                    // если нашли комнаты запихиваем в список (для каждой комнаты свой)
                    first = ft_list_i_head(start->number, map->link);
                    second = ft_list_i_head(tmp->number, map->link);
                    ft_list_add_back_i_or_exit(&first->next, tmp->number, first->next);
                    ft_list_add_back_i_or_exit(&second->next, start->number, second->next);
                    ft_str_print_del(&line);
                    return (1);
                }
                tmp = tmp->next;
            }
            return (is_not_valid("not room in link\n"));
            //return (0);//если комнаты закончились раньше, чем мы её нашли
        }
        start = start->next;
    }// если сюда дошли, значит не нашли первую комнату
    return (is_not_valid("not room in link\n"));
}

/*
копирует список комнат в столбец смежности
по идее список комнат меняться не будет - можно оставить ссылки (?)
для каждой line, которая не коммент заполняем ссылки
*/
int created_links(char *line, t_map *map, t_valid *val_id)
{
    t_room	*tmp;

    tmp = map->rooms;
    while (tmp)
    {
        ft_list_add_back_down(&map->link, ft_list_new_down(tmp->number));
        tmp = tmp->next;
    }
    //зашла уже с лайном сюда - отдельно обработать приходится
    check_links(line, map);
    while ((line = ft_check_cmd(&map->fd)))
    {
        if (ft_strnequ(line, "#", 1))
            return (is_not_valid("end or start in link\n"));
        check_links(line, map);
    }
    if (!line && val_id->start == 2 && val_id->end == 2) /* &&
 * это было для какого то теста, но будет означать что нет пути
 * думаю можно убрать
	ft_list_i_head(map->c_room, map->link)->next != NULL)*/
    {
        free(val_id);
        return (1);
    }
    return (is_not_valid("no start or end\n"));
}


