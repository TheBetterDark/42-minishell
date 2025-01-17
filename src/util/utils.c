/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/17 09:11:04 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Checks if the character is a quote
*
* @param c The character
* @param quote The quote character
*
* @return true if the character is a quote, false otherwise
*/
bool	is_quote(const char c, const char quote)
{
	return (c == quote);
}

/*
* @brief Checks if the character is a blank
*
* @param c The character
*
* @return true if the character is a blank, false otherwise
*/
bool	is_blank(const char c)
{
	return (c == ' ' || c == '\t');
}

/*
* @brief Check if the input matches the test string
*
* @param input The input string
* @param test The test string
*
* @return true if the input matches the test string, false otherwise
*/
bool	input_matches(char *input, char *test)
{
	if (!input || !test)
		return (false);
	if (ft_strcmp(input, test) == 0)
		return (true);
	return (false);
}

/*
* @brief Check if the command is a builtin
*
* @param command The command to check
*
* @return true if the command is a builtin, false otherwise
*/
bool	is_builtin_command(const char *command)
{
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
