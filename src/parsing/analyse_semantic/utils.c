/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:36:10 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 22:40:03 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->args = NULL;
	command->outfile = NULL;
	command->infile = NULL;
	command->limiter_hd = NULL;
	command->redir_lst = NULL;
	command->is_pipe = 0;
	command->cmd_path = NULL;
	command->error_msg = NULL;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

void	add_back_command(t_command **commands, t_command *new_command)
{
	t_command	*last;

	if (!*commands)
	{
		*commands = new_command;
		return ;
	}
	last = *commands;
	while (last->next)
		last = last->next;
	last->next = new_command;
	new_command->prev = last;
}

short	add_arg_command(t_token *token, t_command *command)
{
	int	i;

	if (!command || !token)
		return (1);
	if (!command->args)
	{
		command->args = malloc(sizeof(t_token *) * 2);
		if (!command->args)
			return (1);
		command->args[0] = token;
		command->args[1] = NULL;
	}
	else
	{
		i = 0;
		while (command->args[i])
			i++;
		command->args = realloc(command->args, sizeof(t_token *) * (i + 2));
		if (!command->args)
			return (1);
		command->args[i] = token;
		command->args[i + 1] = NULL;
	}
	return (0);
}
