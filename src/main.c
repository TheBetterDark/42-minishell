/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	nested_shell_count(t_mini *m)
{
	char	*tmp;
	int		lv;
	char	*lv_tmp;

	lv = ft_atoi(getenv("SHLVL")) + 1;
	lv_tmp = ft_itoa(lv);
	tmp = ft_strjoin("SHLVL=", lv_tmp);
	if (!tmp)
	{
		perror("minishell: cd");
		exit(1);
	}
	free(lv_tmp);
	m_export(m, tmp, NULL);
	ft_lstlast(m->env_vars)->next = ft_lstnew(tmp);
}

static void	load_env_variables(t_mini *m)
{
	char	*tmp;

	m_unset(m, "OLDPWD");
	b_pwd(m, 0);
	tmp = ft_strjoin("PWD=", m->path);
	if (!tmp)
	{
		perror("minishell: cd");
		exit(1);
	}
	m_export(m, tmp, NULL);
	ft_lstlast(m->env_vars)->next = ft_lstnew(tmp);
	nested_shell_count(m);
}

void	config_terminal(t_mini *m)
{
	struct termios	termios;

	ft_memset(&m->terminal, 0, sizeof(m->terminal));
	tcgetattr(STDIN_FILENO, &m->terminal);
	termios = m->terminal;
	termios.c_lflag &= ~ECHOCTL;
	termios.c_lflag |= (ECHO | ICANON | ISIG);	
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

int	main(void)
{
	t_mini	m;

	init_signal();
	config_terminal(&m);
	m.exit_status = 0;
	m.env_vars = ft_lstnew(NULL);
	if (!m.env_vars)
	{
		perror("minishell");
		exit(1);
	}
	init_minishell(&m);
	if (init_environment(&m))
	{
		perror("minishell");
		exit(1);
	}
	load_env_variables(&m);
	main_loop(&m);
	ft_free_all(m.env_vars);
	exit(0);
}
