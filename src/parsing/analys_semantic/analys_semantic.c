/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analys_semantic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/01 23:59:46 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	process_token(t_input **current_input, t_command *command)
{
	t_input	*input;

	input = *current_input;
	if (input->token->type == TOKEN_ARGUMENT)
	{
		if (handler_argument(input, command))
			return (1);
	}
	else if (input->token->type >= TOKEN_REDIRECTION_IN
		&& input->token->type <= TOKEN_REDIRECTION_APPEND_OUT)
	{
		if (handler_redirection(input, command))
			return (1);
		if (!command->error_msg)
			*current_input = input->next;
	}
	else if (input->token->type == TOKEN_PIPE)
	{
		if (handler_pipe(input, command))
			return (1);
	}
	return (0);
}

static short	process_command(t_input **current_input, t_command *command)
{
	t_input	*input;

	input = *current_input;
	while (input)
	{
		if (input->token->type >= TOKEN_ARGUMENT
			&& input->token->type <= TOKEN_PIPE)
		{
			if (process_token(&input, command))
				return (1);
		}
		else
			return (*current_input = input, 0);
		input = input->next;
	}
	*current_input = input;
	return (0);
}

short	handler_command(t_input **current_input, t_minishell *env)
{
	t_command	*current_command;

	current_command = create_command((*current_input)->token);
	if (!current_command)
		return (1);
	add_back_command(&env->commands, current_command);
	handler_validate_command(*current_input, current_command);
	*current_input = (*current_input)->next;
	if (process_command(current_input, current_command))
		return (1);
	if (current_command->error_msg)
		return (2);
	return (0);
}

short	analys_semantic(t_minishell *env)
{
	t_input	*current_input;
	short	error_code;

	current_input = env->input;
	while (current_input)
	{
		if (current_input->token->type == TOKEN_COMMAND
			|| current_input->token->type == TOKEN_BUILTIN)
		{
			error_code = handler_command(&current_input, env);
			if (error_code == 1)
				return (1);
			else if (error_code == 2)
				break ;
		}
		else
		{
			ft_fprintf(2, ERR_SYNTAX "unexpected command\n",
				current_input->token->value);
			return (0);
		}
	}
	return (0);
}
