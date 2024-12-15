/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analys_semantic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/16 00:26:47 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SI TU PASSE PAR LA NE REGARDE PAS ICI FAUT QUE JE RANGE ET REFACTO TOUT CA

t_command	*create_command(t_token *token)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->command = token;
	command->args = NULL;
	command->out_file = NULL;
	command->in_file = NULL;
	command->is_pipe = 0;
	command->error_msg = NULL;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

static void	add_back_command(t_command **commands, t_command *new_command)
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

static short	handle_redirection(t_input *input, t_command *command)
{
	t_token	*token;
	t_token	*next;

	token = input->token;
	if (!input->next)
	{
		command->error_msg = ft_strdup("Error: Missing file for redirection");
		// return (1); TODO GERER LES ERREURS
	}
	next = input->next->token;
	if (!(next->type >= TOKEN_BUILTIN || next->type <= TOKEN_ARGUMENT))
	{
		command->error_msg = ft_strdup("Error: Invalid argument for redirection");
		// return (1); TODO GERER LES ERREURS
	}
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

static short	process_command(t_input **current_input, t_command *command)
{
	t_input	*input;

	input = *current_input;
	while (input)
	// DEBUG PROTEC SI ARG APRES UNE REDIR (GERER ICI OU HANDLE LES ERRREUR DE SYNTAXE AVANT ?)
	{
		if (input->token->type == TOKEN_ARGUMENT)
		{
			if (add_arg_command(input->token, command))
				return (1);
		}
		else if (input->token->type >= TOKEN_REDIRECTION_IN
			&& input->token->type <= TOKEN_PIPE)
		{
			if (handle_redirection(input, command))
				return (1);
			if (input->token->type != TOKEN_PIPE)
				// PAS PROPRE A GERER A PART LES PIPES
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
