/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_has.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:51:08 by smoore            #+#    #+#             */
/*   Updated: 2025/01/07 19:23:38 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_str_arr_has(const char **str_arr, const char *str)
{
	const char	**tmp;

	if (!str_arr || !str)
		return (NULL);
	tmp = str_arr;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, str, ft_strlen(str)) == 0)
			return ((char *)*tmp);
		tmp++;
	}
	return (NULL);
}
