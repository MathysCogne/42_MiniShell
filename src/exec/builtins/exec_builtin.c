/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:23:16 by achantra          #+#    #+#             */
/*   Updated: 2025/01/09 01:07:15 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_minishell *env, t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd->value, "echo") && echo(cmd->str_args))
		return (clean_child(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "env") && env_b())
		return (clean_child(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "exit") && exit_b(env, cmd->str_args))
		return (clean_child(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "pwd") && pwd_b())
		return (clean_child(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "cd") && cd(cmd->str_args))
		return (clean_child(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "export") && export_b(cmd->str_args))
		return (clean_child(env), 1);
	/*else if (!ft_strcmp(cmd->cmd->value, "unset") && unset(env,
			cmd->str_args))
			return (clean_child(env), 1);
	*/
	return (clean_child(env), 0);
}
