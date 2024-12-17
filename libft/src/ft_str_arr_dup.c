/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:51:08 by smoore            #+#    #+#             */
/*   Updated: 2024/12/13 16:39:57 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	find_str_arr_size(const char **str_arr)
{
	int	size;

	size = 0;
	while (*str_arr)
	{
		size++;
		str_arr++;
	}
	return (size);
}

char	**ft_str_arr_dup(const char **str_arr)
{
	const char	**result;
	const char	**tmp;
	int			size;

	if (!str_arr)
		return (NULL);
	size = find_str_arr_size(str_arr);
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
	*tmp = NULL;
	return ((char **)result);
}
