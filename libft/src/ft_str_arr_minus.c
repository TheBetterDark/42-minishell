/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_minus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:43:29 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 19:31:56 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	find_size(const char **str_arr)
{
	int		size;

	size = 0;
	while (*str_arr)
	{
		size++;
		str_arr++;
	}
	return (size);
}

char	**ft_str_arr_minus(const char **str_arr, const char *str)
{
	const char	**result;
	const char	**tmp;
	int			size;

	if (!str || !str_arr)
		return (NULL);
	size = find_size(str_arr);
	result = malloc(sizeof(char *) * (size));
	if (!result)
		return (NULL);
	tmp = result;
	while (*str_arr)
	{
		if (ft_strncmp(*str_arr, str, ft_strlen(str)) == 0)
		{
			str_arr++;
			continue ;
		}
		*tmp = ft_strdup(*str_arr);
		str_arr++;
		tmp++;
	}
	*tmp = NULL;
	return ((char **)result);
}
