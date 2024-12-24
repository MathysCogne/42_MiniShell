/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:36:10 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/24 22:36:53 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(t_token *token)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->command = token;
	command->args = NULL;
	command->out_file = NULL;
	command->in_file = NULL;
	command->is_pipe = 0;
	command->error_msg = NULL;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}
