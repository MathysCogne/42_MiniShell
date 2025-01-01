/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:20:47 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/01 23:59:22 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** No pipe before a command
*/
static short	validate_command_token(t_input *input, t_token *token,
		t_token *prev_token, t_command *command)
{
	(void)input;
	(void)token;
	if (prev_token && prev_token->type != TOKEN_PIPE)
	{
		command->error_msg = ft_strdup(ERR_SYNTAX "unexpected command");
		return (1);
	}
	return (0);
}

/*
** Argument alone
*/
static short	validate_argument_token(t_input *input, t_token *token,
		t_token *prev_token, t_command *command)
{
	(void)input;
	if (!prev_token || !(prev_token->type >= TOKEN_BUILTIN
			&& prev_token->type <= TOKEN_REDIRECTION_APPEND_OUT))
	{
		command->error_msg = ft_strdup(ERR_SYNTAX "unexpected argument");
		return (1);
	}
	handler_quote_expand(token, command);
	return (0);
}

/*
** Multiple redir
** No arguments for redir
*/
static short	validate_redirection_token(t_input *input, t_token *token,
		t_token *prev_token, t_command *command)
{
	(void)token;
	if (!prev_token || (prev_token->type != TOKEN_COMMAND
			&& prev_token->type != TOKEN_BUILTIN
			&& prev_token->type != TOKEN_ARGUMENT))
	{
		command->error_msg = ft_strdup(ERR_SYNTAX "unexpected redirection");
		return (1);
	}
	if (!input->next || input->next->token->type != TOKEN_ARGUMENT)
	{
		command->error_msg = ft_strdup(ERR_SYNTAX
				"missing argument for redirection");
		return (1);
	}
	if (input->next && input->next->token->type >= TOKEN_REDIRECTION_IN
		&& input->next->token->type <= TOKEN_REDIRECTION_APPEND_OUT)
	{
		command->error_msg = ft_strdup(ERR_SYNTAX "multiple redirection");
		return (1);
	}
	return (0);
}

/*
** Redirection before the pipe
** No command after the pipe
** Two pipes
*/
static short	validate_pipe_token(t_input *input, t_token *token,
		t_token *prev_token, t_command *command)
{
	(void)token;
	if (!prev_token || (prev_token->type != TOKEN_COMMAND
			&& prev_token->type != TOKEN_BUILTIN
			&& prev_token->type != TOKEN_ARGUMENT))
	{
		command->error_msg = ft_strdup(ERR_SYNTAX "unexpected pipe");
		return (1);
	}
	if (!input->next || (input->next->token->type != TOKEN_COMMAND
			&& input->next->token->type != TOKEN_BUILTIN))
	{
		command->error_msg = ft_strdup(ERR_SYNTAX "missing command after pipe");
		return (1);
	}
	if (input->next && input->next->token->type == TOKEN_PIPE)
	{
		command->error_msg = ft_strdup(ERR_SYNTAX
				"unexpected consecutive pipe");
		return (1);
	}
	return (0);
}

short	handler_validate_command(t_input *input, t_command *command)
{
	t_token	*prev_token;
	t_token	*token;

	prev_token = NULL;
	while (input)
	{
		token = input->token;
		if ((token->type == TOKEN_COMMAND || token->type == TOKEN_BUILTIN)
			&& validate_command_token(input, token, prev_token, command))
			break ;
		else if (token->type == TOKEN_ARGUMENT && validate_argument_token(input,
				token, prev_token, command))
			break ;
		else if (token->type >= TOKEN_REDIRECTION_IN
			&& token->type <= TOKEN_REDIRECTION_APPEND_OUT
			&& validate_redirection_token(input, token, prev_token, command))
			break ;
		else if (token->type == TOKEN_PIPE)
			return (validate_pipe_token(input, token, prev_token, command), 0);
		prev_token = token;
		input = input->next;
	}
	return (0);
}
