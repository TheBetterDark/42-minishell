/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_has.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:51:08 by smoore            #+#    #+#             */
/*   Updated: 2024/12/13 17:11:07 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

bool	ft_str_arr_has(const char **str_arr, const char *str)
{
	const char	**tmp;

	if (!str_arr || !str)
		return (NULL);
	tmp = str_arr;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, str, ft_strlen(str)) == 0)
			return (true);
		tmp++;
	}
	return (false);
}
