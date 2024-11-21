/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:40:50 by muabdi            #+#    #+#             */
/*   Updated: 2024/11/21 16:38:06 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
* @brief Handle the greater than sign
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_greater(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->cursor == '>')
	{
		lexer_advance(lexer);
		return (token_new(TOKEN_APPEND, ft_strdup(">>")));
	}
	return (token_new(TOKEN_TRUNCATE, ft_strdup(">")));
}

/*
* @brief Handle the less than sign
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_less(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->cursor == '<')
	{
		lexer_advance(lexer);
		return (token_new(TOKEN_INPUT, ft_strdup("<<")));
	}
	return (token_new(TOKEN_INPUT, ft_strdup("<")));
}

/*
* @brief Handle the single quote
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_single_quote(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (token_new(TOKEN_QUOTE, ft_strdup("'")));
}

/*
* @brief Handle the double quote
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_double_quote(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (token_new(TOKEN_QUOTE, ft_strdup("\"")));
}

/*
* @brief Handle the pipe sign
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_pipe(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (token_new(TOKEN_PIPE, ft_strdup("|")));
}
