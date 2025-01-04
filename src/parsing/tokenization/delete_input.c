/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:27:24 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 22:52:39 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_input_redir(t_command *current_command)
{
	t_input	*current;
	t_input	*next;

	current = current_command->redir_lst;
	while (current)
	{
		next = current->next;
		free(current->token->value);
		free(current->token);
		free(current);
		current = next;
	}
	current_command->redir_lst = NULL;
}

void	delete_commands(t_minishell *env)
{
	t_command	*current;
	t_command	*next;
	int			i;

	current = env->cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				i++;
			free(current->args);
		}
		if (current->error_msg)
			free(current->error_msg);
		if (current->str_args)
			free(current->str_args);
		if (current->redir_lst)
			delete_input_redir(current);
		free(current);
		current = next;
	}
	env->cmds = NULL;
}

/*
** Clean and free input and token after use
*/
void	delete_input(t_minishell *env)
{
	t_input	*current;
	t_input	*next;

	current = env->input;
	while (current)
	{
		next = current->next;
		free(current->token->value);
		free(current->token);
		free(current);
		current = next;
	}
	env->input = NULL;
	free_split(env->envp);
	delete_commands(env);
}
