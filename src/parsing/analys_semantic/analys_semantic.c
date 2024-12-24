/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analys_semantic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/24 22:36:32 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static short	add_arg_command(t_token *token, t_command *command)
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

static short	handler_redirection(t_input *input, t_command *command)
{
	t_token	*token;
	t_token	*next;

	token = input->token;
	if (!input->next)
		command->error_msg = ft_strdup("Missing file for redirection");
	next = input->next->token;
	if (!(next->type >= TOKEN_BUILTIN || next->type <= TOKEN_ARGUMENT))
		command->error_msg = ft_strdup("Invalid argument for redirection");
	if (token->type == TOKEN_REDIRECTION_IN)
		command->in_file = next;
	else if (token->type == TOKEN_REDIRECTION_OUT)
		command->out_file = next;
	else if (token->type == TOKEN_HEREDOC)
		command->out_file = next;
	if (token->type == TOKEN_PIPE)
		command->is_pipe = 1;
	return (0);
}

// DEBUG PROTEC SI ARG APRES UNE REDIR
// (GERER ICI OU HANDLER LES ERRREUR DE SYNTAXE AVANT ?)
// MOI DU PASSER DIT APRES LORS DE LEXEC
static short	process_command(t_input **current_input, t_command *command)
{
	t_input	*input;

	input = *current_input;
	while (input)
	{
		if (input->token->type == TOKEN_ARGUMENT)
		{
			if (add_arg_command(input->token, command))
				return (1);
		}
		else if (input->token->type >= TOKEN_REDIRECTION_IN
			&& input->token->type <= TOKEN_PIPE)
		{
			if (handler_redirection(input, command))
				return (1);
			if (input->token->type != TOKEN_PIPE)
				input = input->next;
		}
		else
			break ;
		input = input->next;
	}
	*current_input = input;
	return (0);
}

short	analys_semantic(t_minishell *env)
{
	t_input		*current_input;
	t_command	*current_command;

	current_input = env->input;
	while (current_input)
	{
		if (current_input->token->type == TOKEN_COMMAND
			|| current_input->token->type == TOKEN_BUILTIN)
		{
			current_command = create_command(current_input->token);
			if (!current_command)
				return (1);
			add_back_command(&env->commands, current_command);
			current_input = current_input->next;
			if (process_command(&current_input, current_command))
				return (1);
		}
		else
			current_input = current_input->next;
	}
	return (0);
}
