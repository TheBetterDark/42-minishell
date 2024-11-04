/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "minishell.h"

bool	parse_redirect_and_heredoc(t_mini *m);
bool	parse_fd(t_mini *m);
bool	parse_command_line(t_mini *m);
t_token	*find_cmd_after_pipe(t_token *now);
bool	rdr_malloc(t_mini *m, int idx);
void	set_default_fds(t_cmd *cmd, int idx, t_token *type, t_token *fn);
void	set_custom_fds(t_cmd *cmd, int idx, t_token *fd, t_token *fn);
#endif
