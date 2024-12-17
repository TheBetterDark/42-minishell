/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/16 17:12:55 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	free_minishell(t_data *d)
{
	free(d->input);
	d->cmd_ct = 0;
	tok_lstclear(&d->toks);
	d->input_fd = 0;
	d->output_fd = 1;
	d->r_input_fd = -1;
	d->r_output_fd = -1;
}
