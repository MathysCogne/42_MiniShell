/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_and_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:24:49 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 22:01:58 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	find_path_and_cmd(t_minishell *env, t_command *command)
{
	t_token	*cmd;

	if (!command->args || !command->args[0])
		return (0);
	cmd = command->args[0];
	command->cmd = cmd;
	command->cmd_path = NULL;
	env->envp = NULL;
	if (is_builtin_command(cmd->value))
		cmd->type = TOKEN_BUILTIN;
	else
	{
		command->cmd_path = is_external_command(env, cmd->value);
		if (command->cmd_path)
			cmd->type = TOKEN_COMMAND;
	}
	return (0);
}
