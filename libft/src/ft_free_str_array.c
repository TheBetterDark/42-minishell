/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:51:35 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 07:53:55 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_str_arr(char ***str_arr_ptr)
{
	char	**str_arr;
	char	**tmp;

	str_arr = *str_arr_ptr;
	if (!str_arr)
		return ;
	tmp = str_arr;
	while (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	free(str_arr);
	*str_arr_ptr = NULL;
}
