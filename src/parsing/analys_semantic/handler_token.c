/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/01 23:02:28 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	handler_redirection(t_input *input, t_command *command)
{
	t_token	*token;
	t_token	*next;

	token = input->token;
	if (!input->next)
		return (0);
	next = input->next->token;
	if (token->type == TOKEN_REDIRECTION_IN)
		command->in_file = next;
	else if (token->type == TOKEN_REDIRECTION_OUT)
		command->out_file = next;
	else if (token->type == TOKEN_HEREDOC)
		command->out_file = next;
	else if (token->type == TOKEN_REDIRECTION_APPEND_OUT)
		command->out_file = next;
	return (0);
}

short	handler_pipe(t_input *input, t_command *command)
{
	if (!input->next)
		return (0);
	command->is_pipe = 1;
	return (0);
}

short	handler_argument(t_input *input, t_command *command)
{
	if (command->error_msg)
		return (0);
	add_arg_command(input->token, command);
	return (0);
}
