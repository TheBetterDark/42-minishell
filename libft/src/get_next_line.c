/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:36:15 by smoore            #+#    #+#             */
/*   Updated: 2024/01/27 13:23:59 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	push_new_tail(t_list_len **head, char *str, size_t len)
{
	t_list_len	*new;
	t_list_len	*current;

	new = malloc(sizeof(t_list_len));
	new->len = len;
	new->str = str;
	new->str[len] = '\0';
	new->next = NULL;
	if (!new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	examine_buf(t_list_len	**head, char *buf)
{
	size_t	start;
	size_t	len;

	start = 0;
	while (buf[start] != '\0')
	{
		len = 0;
		if (buf[start + len] == '\n')
			len++;
		else
		{
			while (buf[start + len] != '\n' && buf[start + len] != '\0')
				len++;
			if (buf[start + len] == '\n')
				len++;
		}
		push_new_tail(head, gnl_substr(buf, start, len), len);
		start = start + len;
	}
}

void	read_file(t_list_len **head, int fd)
{
	ssize_t		nbytes;
	char		*buf;

	while (!has_newline(*head))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (!nbytes || nbytes == -1)
		{
			free(buf);
			return ;
		}
		buf[nbytes] = '\0';
		examine_buf(head, buf);
		free(buf);
	}
}

char	*make_line(t_list_len **head)
{
	char		*next_ln;
	size_t		len;
	size_t		i;
	int			j;

	if (*head == NULL)
		return (NULL);
	len = len_of_newline(*head);
	next_ln = malloc(len + 1);
	if (!next_ln)
		return (NULL);
	i = 0;
	while (i < len)
	{
		j = 0;
		while ((*head)->str[j] != '\0')
			next_ln[i++] = (*head)->str[j++];
		pop_head(head);
	}
	next_ln[i] = '\0';
	return (next_ln);
}

char	*get_next_line(int fd)
{
	static t_list_len	*head;
	char				*next_ln;

	if (fd < 0 || fd > 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!head)
		head = NULL;
	read_file(&head, fd);
	next_ln = make_line(&head);
	return (next_ln);
}
/*
int	main(void)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	while (i < 16)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	return (0);
}*/
