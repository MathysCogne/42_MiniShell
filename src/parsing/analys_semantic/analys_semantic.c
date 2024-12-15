/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analys_semantic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/15 16:55:31 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	handler_redirection(t_input *input, t_command *command)
{
	t_token	*current;
	t_token	*next;

	if (!input || !command)
		return (1);
	if (!input->next)
	{
		if (!command->error_msg)
			command->error_msg = ft_strdup("Error: Missing file for redirection");
		return (1);
	}
	current = input->token;
	next = input->next->token;
	if (next->type == TOKEN_ARGUMENT)
		current->target_file = next->value;
	else
	{
		if (!command->error_msg)
			command->error_msg = ft_strdup("Error: Invalid argument for redirection");
		return (1);
	}
	return (0);
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

short	handler_args_command(t_input *input, t_command *command)
{
	t_input	*current;

	if (!input || !command)
		return (1);
	current = input->next;
	// NOTE: GESTION DES MESSAGES DERREUR DE SYNTAXE DANS LEXEC SI ARG NECCESSAIRE
	while (current && current->token->type == TOKEN_ARGUMENT)
	{
		if (add_arg_command(current->token, command))
			return (1);
		current = current->next;
	}
	return (0);
}

t_command	*create_command(t_token *token)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command = token->value;
	command->args = NULL;
	command->out_file = NULL;
	command->in_file = NULL;
	command->is_pipe = 0;
	command->error_msg = NULL;
	return (command);
}

short	analys_semantic(t_minishell *env)
{
	t_command	*command;
	t_input		*current;

	current = env->input;
	while (current)
	{
		if (current->token->type == TOKEN_COMMAND)
		{
			command = create_command(current->token->value);
			if (!command)
				return (1);
			if (handler_args_command(current, command))
				return (1);
		}
		else if (current->token->type >= TOKEN_REDIRECTION_IN
			&& current->token->type <= TOKEN_PIPE)
		{
			handler_redirection(current, command);
		}
		current = current->next;
	}
	return (0);
}
