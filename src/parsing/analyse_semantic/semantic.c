/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/09 18:33:31 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	process_token(t_input **current_input, t_command *command)
{
	t_input	*input;

	input = *current_input;
	if (input->token->type == TOKEN_ARGUMENT)
	{
		if (add_arg_command(input->token, command))
			return (1);
	}
	else if (input->token->type >= TOKEN_REDIRECTION_IN
		&& input->token->type <= TOKEN_REDIRECTION_APPEND_OUT)
	{
		if (handler_redirection(input, command))
			return (1);
		input = input->next;
		*current_input = input;
	}
	else if (input->token->type == TOKEN_PIPE)
	{
		command->is_pipe = 1;
		return (2);
	}
	return (0);
}

static short	process_command(t_input **current_input, t_command *command)
{
	t_input	*input;
	short	error_code;

	input = *current_input;
	while (input)
	{
		error_code = process_token(&input, command);
		if (error_code == 1)
			return (1);
		else if (error_code == 2 && input->next)
		{
			input = input->next;
			*current_input = input;
			return (0);
		}
		if (!input)
			return (*current_input = input, 0);
		input = input->next;
	}
	*current_input = input;
	return (0);
}

static short	handler_command(t_input **current_input, t_minishell *env)
{
	t_command	*current_command;

	current_command = create_command();
	if (!current_command)
		return (1);
	add_back_command(&env->cmds, current_command);
	handler_validate_command(env, *current_input, current_command);
	if (process_command(current_input, current_command))
		return (1);
	if (find_path_and_cmd(env, current_command))
		return (1);
	if (extract_args(current_command))
		return (1);
	return (0);
}

short	analyse_semantic(t_minishell *env)
{
	t_input	*current_input;

	current_input = env->input;
	while (current_input)
	{
		if (handler_command(&current_input, env))
			return (1);
	}
	return (0);
}
