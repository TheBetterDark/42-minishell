/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "minishell.h"

typedef struct s_sort
{
	t_token	*a_cur;
	t_token	*b_cur;
	int		a_i;
	int		b_i;
}				t_sort;

bool	handle_quotes(t_mini *m);
bool	tokenize_input(t_mini *m);
bool	redirection(t_mini *m);
void	merge_sort_tokens(t_mini *m);
bool	extract_tokens(t_mini *m, char *str, char *delims);

bool	merge_adjacent_tokens(t_mini *m);
bool	tokenize_pipeline(t_mini *m);
void	assign_token_type(t_mini *m);

#endif
