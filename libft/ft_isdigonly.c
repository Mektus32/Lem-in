/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigonly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:18:02 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/15 19:18:03 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isdigonly(char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = -1;
	while (str[++i] != '\0')
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
	if (len > 0)
		return (1);
	return (0);
}
