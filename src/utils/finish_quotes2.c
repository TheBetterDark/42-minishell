/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:14:43 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 14:05:24 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*complete_quoted_input(char *input);

char	*complete_quoted_input(char *input)
{
	int		i;
	int		delim;

	if (!has_quotes(input))
		return (input);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			delim = input[i];
			i++;
			while (input[i] && input[i] != delim)
				i++;
			if (!input[i])
				return (free(input), finish_quotes(input));
			else
				i++;
		}
		else
			i++;
	}
	return (input);
}
