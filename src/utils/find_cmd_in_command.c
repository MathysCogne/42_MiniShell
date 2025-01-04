/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_in_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:24:49 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 04:50:04 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	find_cmd_in_command(t_minishell *env, t_command *command)
{
	t_token	*cmd;

	if (!command->args || !command->args[0])
		return (0);
	cmd = command->args[0];
	command->cmd = cmd;
	command->cmd_path = NULL;
	if (is_internal_command(cmd->value))
		cmd->type = TOKEN_BUILTIN;
	else if (is_external_command(env, cmd->value) != NULL)
	{
		cmd->type = TOKEN_COMMAND;
		command->cmd_path = is_external_command(env, cmd->value);
	}
	return (0);
}
