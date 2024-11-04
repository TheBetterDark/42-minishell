/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

void	cd_to_home(t_mini *m, int idx)
{
	if (chdir(getenv("HOME")) != 0)
		cd_error(m, idx);
	mod_env_cd(m, getenv("PWD"));
}

void	mod_env_cd(t_mini *m, char *old_pwd)
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
	b_pwd(m, 0);
	tmp = ft_strjoin("PWD=", m->path);
	if (!tmp)
	{
		perror("minishell: cd");
		if (m->job_size != 1)
			exit(errno);
	}
	m_export(m, tmp, "cd");
	free(tmp);
}

void	cd_error(t_mini *m, int idx)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (errno == EFAULT && !ft_strncmp(m->cmd[idx].args[1], "-", 2))
		ft_putstr_fd("OLDPWD not set\n", 2);
	else
		perror(m->cmd[idx].args[1]);
	if (m->job_size != 1)
		exit(1);
	m->exit_status = 1;
}

void	b_cd_handle(t_mini *m, int idx)
{
	int	flag;
	int	cmp;

	flag = chdir(m->cmd[idx].args[1]);
	cmp = ft_strncmp(m->cmd[idx].args[1], ".", 2);
	if (flag == -1)
		cd_error(m, idx);
	else if (!cmp)
	{
		if (access(getenv("PWD"), F_OK) != 0)
			cd_error_special(m);
		else
			mod_env_cd(m, getenv("PWD"));
	}
	else
		mod_env_cd(m, getenv("PWD"));
}

void	b_cd(t_mini *m, int idx)
{
	if (!m->cmd[idx].args[1])
		cd_to_home(m, idx);
	else if (ft_strncmp(m->cmd[idx].args[1], "~", 2) == 0 ||
		!m->cmd[idx].args[1] ||
		ft_strncmp(m->cmd[idx].args[1], "~/", 3) == 0)
		cd_to_home(m, idx);
	else if (ft_strncmp(m->cmd[idx].args[1], "-", 2) == 0
		|| ft_strncmp(m->cmd[idx].args[1], "-/", 3) == 0)
	{
		if (chdir(getenv("OLDPWD")) != 0)
			cd_error(m, idx);
		else
			printf("%s\n", getenv("OLDPWD"));
		mod_env_cd(m, getenv("PWD"));
	}
	else
		b_cd_handle(m, idx);
	if (m->job_size != 1)
		exit(0);
}
