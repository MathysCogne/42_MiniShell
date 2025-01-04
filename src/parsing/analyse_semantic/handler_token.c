/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 04:15:34 by mcogne--         ###   ########.fr       */
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
		command->infile = next;
	else if (token->type == TOKEN_REDIRECTION_OUT)
		command->outfile = next;
	else if (token->type == TOKEN_HEREDOC)
		command->limiter_herdoc = next;
	else if (token->type == TOKEN_REDIRECTION_APPEND_OUT)
		command->outfile_append = next;
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
