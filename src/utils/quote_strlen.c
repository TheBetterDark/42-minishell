/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_strlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:51:57 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 13:33:49 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	quoted_strlen_util(char *str, int *i);
int			quoted_strlen(char *str);

static void	quoted_strlen_util(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
			(*i)++;
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
		if (str[*i] == '\"')
			(*i)++;
	}
	else
	{
		while (str[*i] && !is_blank(str[*i])
			&& !is_quote(str[*i]) && !is_symbol(str[*i]))
			(*i)++;
	}
}

int	quoted_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_blank(str[i]) && !is_symbol(str[i]))
	{
		quoted_strlen_util(str, &i);
	}
	return (i);
}
