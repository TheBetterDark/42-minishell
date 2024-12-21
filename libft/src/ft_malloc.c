/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:25:01 by smoore            #+#    #+#             */
/*   Updated: 2023/11/12 17:58:20 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_malloc(size_t size, t_list *mem)
{
	void	*new;
	t_list	*tail;

	new = malloc(size);
	if (!new)
	{
		ft_free_all(mem);
		return (NULL);
	}
	tail = ft_lstlast(mem);
	tail->next = ft_lstnew(new);
	return (new);
}
