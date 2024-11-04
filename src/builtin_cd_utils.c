/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

static void	mod_env_cd_oldpwd(t_mini *m, char *old_pwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
	{
		perror("minishell: cd");
		if (m->job_size != 1)
			exit(errno);
	}
	m_export(m, tmp, "cd");
	free(tmp);
}

void	mod_env_cd_special(t_mini *m, char *old_pwd)
{
	char	*tmp;
	char	*new_pwd;

	mod_env_cd_oldpwd(m, old_pwd);
	b_pwd(m, 0);
	tmp = ft_strjoin("PWD=", m->path);
	if (!tmp)
	{
		perror("minishell: cd");
		if (m->job_size != 1)
			exit(errno);
	}
	new_pwd = ft_strjoin(tmp, "/.");
	if (!tmp)
	{
		free(tmp);
		perror("minishell: cd");
		if (m->job_size != 1)
			exit(errno);
	}
	m_export(m, new_pwd, "cd");
	free(new_pwd);
	free(tmp);
}

void	cd_error_special(t_mini *m)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
	ft_putstr_fd(" cannot access parent directories:", 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	mod_env_cd_special(m, getenv("PWD"));
	if (m->job_size != 1)
		exit(1);
	m->exit_status = 1;
}
