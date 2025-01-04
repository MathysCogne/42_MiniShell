/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 22:58:22 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Manage put token For redir
** Create Node token and input before add
*/
short	put_input_redir(t_command *current_command, char *value,
		t_token_type type)
{
	t_token	*new_token;
	t_input	*new_input;

	new_token = create_token(value, type);
	if (!new_token)
		return (1);
	new_input = create_input(new_token);
	if (!new_input)
		return (1);
	input_add_back(&current_command->redir_lst, new_input);
	return (0);
}

short	handler_redirection(t_input *input, t_command *command)
{
	t_token	*token;
	t_token	*next;

	token = input->token;
	if (!input->next)
		return (0);
	next = input->next->token;
	if (token->type == TOKEN_REDIRECTION_IN)
	{
		if (put_input_redir(command, next->value, TOKEN_REDIRECTION_IN))
			return (1);
	}
	else if (token->type == TOKEN_REDIRECTION_OUT)
	{
		if (put_input_redir(command, next->value, TOKEN_REDIRECTION_OUT))
			return (1);
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		if (put_input_redir(command, next->value, TOKEN_HEREDOC))
			return (1);
	}
	else if (token->type == TOKEN_REDIRECTION_APPEND_OUT)
	{
		if (put_input_redir(command, next->value, TOKEN_REDIRECTION_APPEND_OUT))
			return (1);
	}
	return (0);
}

short	handler_pipe(t_input *input, t_command *command)
{
	(void)input;
	command->is_pipe = 1;
	return (0);
}

short	handler_argument(t_input *input, t_command *command)
{
	add_arg_command(input->token, command);
	return (0);
}
