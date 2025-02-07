/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:35:30 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:42:41 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

int		count_words(char *line);
char	**allocate_words_memory(char *line);

int	count_words(char *line)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (line[i])
	{
		while (is_blank(line[i]))
			i++;
		if (is_symbol(line[i]))
		{
			size++;
			i++;
			if (line[i] == line[i - 1] && line[i] != '|')
				i++;
		}
		else if (line[i])
		{
			size++;
			i += quoted_strlen(&line[i]);
		}
	}
	return (size);
}

char	**allocate_words_memory(char *line)
{
	char	**words;
	int		size;

	size = count_words(line);
	words = malloc(sizeof(char *) * (size + 1));
	if (!words)
		return (NULL);
	words[size] = NULL;
	return (words);
}
