/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:02:49 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 12:15:26 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

bool	has_quotes(char *str);
bool	calculate_if_finished(int single_quotes, int double_quotes);
bool	has_finished_quotes(char *str);
char	get_last_quote(char *input);

bool	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	calculate_if_finished(int single_quotes, int double_quotes)
{
	bool	finished;

	finished = false;
	if ((single_quotes % 2 == 0) && (double_quotes % 2 == 0))
		finished = true;
	else
		finished = false;
	return (finished);
}

bool	has_finished_quotes(char *str)
{
	int		i;
	int		single_quotes;
	int		double_quotes;
	bool	finished;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	finished = false;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == '\"')
			double_quotes++;
		i++;
	}
	finished = calculate_if_finished(single_quotes, double_quotes);
	return (finished);
}

char	get_last_quote(char *input)
{
	int		len;
	int		i;

	len = ft_strlen(input) - 1;
	i = 0;
	while (i < len)
	{
		if (is_quote(input[len]))
			return (input[len]);
		len--;
	}
	return ('x');
}
