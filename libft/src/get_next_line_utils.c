/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:57:13 by smoore            #+#    #+#             */
/*   Updated: 2024/01/27 13:05:44 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	has_newline(t_list_len *head)
{
	int	i;

	if (!head)
		return (0);
	while (head)
	{
		i = 0;
		while (head->str[i] && i < BUFFER_SIZE)
		{
			if (head->str[i] == '\n')
				return (1);
			i++;
		}
		head = head->next;
	}
	return (0);
}

void	pop_head(t_list_len **head)
{
	t_list_len	*temp;

	temp = NULL;
	if (*head == NULL)
		return ;
	temp = (*head)->next;
	free((*head)->str);
	free(*head);
	*head = temp;
}

char	*gnl_substr(char const *s, size_t start, size_t size)
{
	char	*substr;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	if (start > len)
		size = len;
	if (len - start < size)
		size = len - start;
	substr = malloc(size + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < size)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

size_t	len_of_newline(t_list_len *head)
{
	size_t	i;
	size_t	len;

	if (head == NULL)
		return (0);
	len = 0;
	while (head)
	{
		i = 0;
		while (head->str[i])
		{
			if (head->str[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		head = head->next;
	}
	return (len);
}
