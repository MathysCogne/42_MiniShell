/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:27:24 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/03 11:59:01 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	delete_commands(env);
}
