/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:54:36 by ojessi            #+#    #+#             */
/*   Updated: 2019/04/09 20:29:46 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int i;
	int	j;

	i = 0;
	if (!str2[0])
		return ((char*)str1);
	while (str1[i] != '\0')
	{
		j = 0;
		while (str2[j] != '\0' && str2[j] == str1[i + j] && str1[j + i] != '\0')
			j++;
		if (!str2[j])
			return ((char*)&str1[i]);
		i++;
	}
	return (NULL);
}
// char	*ft_strstr(const char *str, const char *to_find)
// {
// 	int i;
// 	int k;

// 	i = 0;
// 	k = 0;
// 	if (to_find[k] == '\0')
// 		return ((char *)str + i);
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] != to_find[0] && str[i] != '\0')
// 			i++;
// 		if (str[i] == '\0')
// 			return (0);
// 		while (str[i] == to_find[k] && str[i] != '\0' && to_find[k++] != '\0')
// 			i++;
// 		if (to_find[k] == '\0')
// 			return ((char *)str + i - k);
// 		else
// 		{
// 			i = i - k + 1;
// 			k = 0;
// 		}
// 	}
// 	return (0);
// }