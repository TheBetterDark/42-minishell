/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:53:48 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/26 23:03:32 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef HOST_NAME_MAX
#  define HOST_NAME_MAX 256
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

typedef struct s_prompt
{
	char		hostname[HOST_NAME_MAX];
	char		cwd[PATH_MAX];
	char		*user;
}				t_prompt;

typedef struct s_data
{
	t_prompt	*prompt;
}				t_data;

t_prompt		*initialize_prompt(void);
char			*display_prompt(t_prompt *prompt);

int				initalize_signals(void);

int				ft_getcwd(char *cwd, bool is_tilde);
int				ft_gethostname(char *hostname);

#endif
