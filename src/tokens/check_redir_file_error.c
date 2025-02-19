/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_file_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 15:08:00 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

bool	check_redir_file_error(t_token *symbol, t_token *file)
{
	if (symbol->type == RE_READ && file->type != FN_READ)
		return (true);
	else if (symbol->type == RE_TRUNC && file->type != FN_TRUNC)
		return (true);
	else if (symbol->type == RE_APPEND && file->type != FN_APPEND)
		return (true);
	else if (symbol->type == RE_HEREDOC && file->type != DELIM)
		return (true);
	else
		return (false);
}
