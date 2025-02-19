/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:14:43 by smoore            #+#    #+#             */
/*   Updated: 2025/02/18 15:11:49 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*complete_quoted_input(char *input);

char	*complete_quoted_input(char *input)
{
	char	*new_input;
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
			{
				new_input = finish_quotes(input);
				return (new_input);
			}	
			else
				i++;
		}
		else
			i++;
	}
	return  (input);
}
