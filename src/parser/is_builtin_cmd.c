/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:37:40 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:35:41 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

bool	is_builtin_cmd(char *cmdv)
{
	const char	*builtins[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};
	int			i;

	if (!cmdv)
		return (NULL);
	i = 0;
	while (i < 7)
	{
		if (word_match(cmdv, (char *)builtins[i]))
			return (true);
		i++;
	}
	return (false);
}
