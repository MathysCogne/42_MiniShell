/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:23:16 by achantra          #+#    #+#             */
/*   Updated: 2025/01/07 12:23:44 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_minishell *env, t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd->value, "echo") && echo(cmd->str_args))
		return (gc_clean(env->gc), delete_input(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "env") && env_b())
		return (gc_clean(env->gc), delete_input(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "exit"))
		return (gc_clean(env->gc), delete_input(env), exit(0), 0);
	else if (!ft_strcmp(cmd->cmd->value, "pwd") && pwd_b())
		return (gc_clean(env->gc), delete_input(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "cd") && cd(cmd->str_args))
		return (gc_clean(env->gc), delete_input(env), 1);
	/*
	else if (!ft_strcmp(cmd->cmd->value, "export") && export(cmd->str_args))
			return (gc_clean(env->gc), delete_input(env), 1);
	else if (!ft_strcmp(cmd->cmd->value, "unset") && unset(env, cmd->str_args))
			return (gc_clean(env->gc), delete_input(env), 1);
	*/
	return (gc_clean(env->gc), delete_input(env), 0);
}
