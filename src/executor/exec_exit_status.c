/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/23 22:05:57 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	catch_exit_status(pid_t pid, t_data *d)
{
	waitpid(pid, &d->exit_stat, 0);
	d->exit_stat = WEXITSTATUS(d->exit_stat);
}

// waitpid(pid, &d->exit_stat, WNOHANG);
