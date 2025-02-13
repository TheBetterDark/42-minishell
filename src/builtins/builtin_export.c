/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/13 15:14:30 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static char	*get_environment_variable(char *env_var, t_data *data);;
static char	*find_env_match(char *key, char **env);
static void	print_env(t_data *data);
static void	error_util(void);
void		builtin_export(t_data *data, char **export_str);

static char	*find_env_match(char *key, char **env)
{
	char	**env_cur;
	char	*potential_key;

	env_cur = env;
	while (*env_cur)
	{
		potential_key = get_key(*env_cur);
		if (word_match(potential_key, key))
		{
			free(potential_key);
			return (*env_cur);
		}
		free(potential_key);
		env_cur++;
	}
	return (NULL);
}

static char	*get_environment_variable(char *env_var, t_data *data)
{
	char	*value;

	value = NULL;
	if (env_var)
		value = find_env_match(get_key(env_var), data->env);
	if (!value)
		return (NULL);
	return (value);
}

static void	print_env(t_data *data)
{
	char	**tmp;

	tmp = data->env;
	while (*tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(*tmp, STDOUT_FILENO);
		tmp++;
	}
}

static void	error_util(void)
{
	perror("export failed");
	exit(EXIT_FAILURE);
}

void	builtin_export(t_data *data, char **export_str)
{
	char	**new_env;
	char	*cur_env_var;
	size_t	new_value_len;

	export_str++;
	new_env = NULL;
	cur_env_var = NULL;
	if (!*export_str)
	{
		print_env(data);
		return ;
	}
	while (*export_str)
	{
		if (!ft_strchr(*export_str, '='))
		{
			data->exit_stat = 1;
			return ;
		}
		cur_env_var = get_environment_variable(*export_str, data);
		if (cur_env_var)
        {
            // Replace memory safely
            new_value_len = strlen(*export_str);
            if (new_value_len <= strlen(cur_env_var))
            {
                strncpy(cur_env_var, *export_str, new_value_len);
                cur_env_var[new_value_len] = '\0';
            }
            else
            {
                // Allocate new memory if the new value is larger
                char *new_var = strdup(*export_str);
                if (!new_var)
                    error_util();
                free(cur_env_var);
                cur_env_var = new_var;
            }
        }
		else
		{
			new_env = ft_str_arr_add((const char **)data->env, *export_str);
			ft_str_arr_free(&data->env);
			if (!new_env)
				error_util();
				data->env = new_env;
		}
		export_str++;
	}
}
