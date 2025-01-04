/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:51:35 by smoore            #+#    #+#             */
/*   Updated: 2025/01/04 16:31:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
void	ft_free_str_arr(char **str_arr)
{
	char **tmp;

	tmp = str_arr;
	while (*tmp)
	{
		printf("Freeing: %p -> %s\n", *tmp, *tmp);
		free(*tmp);
		*tmp = NULL; //
		tmp++;
	}
	free(str_arr);
	str_arr = NULL; //
}
*/
void	ft_free_str_arr(char ***str_arr_ptr)
{
    char **str_arr;
    char **tmp;

    str_arr = *str_arr_ptr;
    if (!str_arr)
        return;
    tmp = str_arr;
    while (*tmp)
    {
       // printf("Freeing: %p -> %s\n", *tmp, *tmp);
        free(*tmp);
        *tmp = NULL;
        tmp++;
    }
    free(str_arr);
    *str_arr_ptr = NULL;
}
