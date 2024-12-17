/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:43:29 by smoore            #+#    #+#             */
/*   Updated: 2024/12/13 15:25:22 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	find_size(const char **str_arr)
{
	const char	**tmp;
	int		size;

	size = 1;
	tmp = str_arr;
	while (*str_arr)
	{
		size++;
		str_arr++;
	}
	return (size);
}

char	**ft_str_arr_add(const char **str_arr, const char *str)
{
	const char	**result;
	const char	**tmp;
	int			size;

	if (!str || !str_arr)
		return (NULL);
	size = find_size(str_arr);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	tmp = result;
	while (*str_arr)
	{
		*tmp = ft_strdup(*str_arr);
		tmp++;
		str_arr++;
	}
	*tmp = ft_strdup(str);
	tmp++;
	*tmp = NULL;
	return ((char **)result);
}
