/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:51:35 by smoore            #+#    #+#             */
/*   Updated: 2024/11/25 16:36:17 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_str_arr(char **str_arr)
{
	char **tmp;

	tmp = str_arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(str_arr);
}
