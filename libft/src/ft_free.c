/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:44:09 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:44:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_all(t_list *mem);
void	ft_free(void *ptr, t_list *mem);

void	ft_free(void *ptr, t_list *mem)
{
	t_list	*prev;

	if (!mem || !ptr)
		return ;
	prev = mem;
	mem = mem->next;
	while (mem)
	{
		if (mem->content == ptr)
		{
			prev->next = mem->next;
			ft_lstdelone(mem, &free);
			break ;
		}
		prev = mem;
		mem = mem->next;
	}
}

void	ft_free_all(t_list *mem)
{
	if (!mem)
		return ;
	ft_lstclear(&mem->next, &free);
}
