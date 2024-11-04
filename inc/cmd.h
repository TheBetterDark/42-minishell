/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

bool	cmd_init(t_mini *m);
bool	is_command(t_mini *m);
bool	cmd_rdin(t_mini *m);
bool	cmd_rdout(t_mini *m);
bool	cmd_append(t_mini *m);
void	cmd_redir(t_mini *m);
bool	is_heredoc(t_mini *m);
bool	create_pipe_for_cmd(t_mini *m, int idx);
void	b_echo(t_mini *m, int idx);
void	b_cd(t_mini *m, int idx);
void	b_export(t_mini *m, int idx);
void	b_unset(t_mini *m, int idx);
void	b_env(t_mini *m, int idx);
void	b_exit(t_mini *m, int idx, bool is_print);
void	execute_builtin(t_mini *m, int idx, bool is_print);
void	execute_cmd(t_mini *m, int idx);
char	**get_path(t_mini *m, char *cmd);
void	cd_error_special(t_mini *m);
void	b_cd_handle(t_mini *m, int idx);
void	mod_env_cd(t_mini *m, char *old_pwd);
void	cd_error(t_mini *m, int idx);
void	mod_env_cd_special(t_mini *m, char *old_pwd);
void	cd_to_home(t_mini *m, int idx);
void	is_a_dir(char *str);
void	check_if_dir(char *cmd);

#endif
