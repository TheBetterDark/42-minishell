/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:51:35 by smoore            #+#    #+#             */
/*   Updated: 2023/11/11 12:15:42 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	word_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*make_word(const char *start, const char *end)
{
	char	*word;
	char	*ptr;

	word = (char *)malloc(end - start + 1);
	ptr = word;
	while (start < end)
	{
		*ptr = *start;
		ptr++;
		start++;
	}
	*ptr = '\0';
	return (word);
}

static void	fill_words(char **split, char const *s, char c)
{
	int			i;
	char const	*start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			split[i] = make_word(start, s);
			i++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	if (s == NULL)
		return (NULL);
	words = word_count(s, c);
	split = malloc((sizeof(char *)) * (words + 1));
	if (split == NULL)
		return (NULL);
	fill_words(split, s, c);
	split[words] = NULL;
	return (split);
}
