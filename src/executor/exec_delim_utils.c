/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delim_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/24 17:48:16 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	measure_substr(char *eof, int *pos, int *start)
{
	char c;

	c = eof[*pos];
	if (c == '\'' || c  == '\"')
	{
		if (eof[*pos] == c)
		{
			(*pos)++;
			*start = *pos;
			while (eof[*pos] && eof[*pos] != c)
				(*pos)++;
		}
	}
	else
	{
		*start = *pos;
		while (eof[*pos] && (eof[*pos] != '\'' || eof[*pos] != '\"'))
			(*pos)++;
	}
}

char	*process_delimiter(char *eof)
{
	int		pos;
	int		start;
	char	*str1;
	char	*str2;
	char	*result;
	
	pos = 0;
	start = 0;
	result = ft_strdup("");
	while (eof[pos])
	{
		measure_substr(eof, &pos, &start);
		str1 = result;
		str2 = ft_substr(eof, start, (pos - start));
		result = ft_strjoin(str1, str2);
		pos++;
	}
	return (result);
}
