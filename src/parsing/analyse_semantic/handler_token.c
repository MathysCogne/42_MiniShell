/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 18:20:05 by achantra         ###   ########.fr       */
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
	{
		command->infile = next;	
		command->infile->type = TOKEN_REDIRECTION_IN;
	}
	else if (token->type == TOKEN_REDIRECTION_OUT)
	{
		command->outfile = next;
		command->outfile->type = TOKEN_REDIRECTION_OUT;
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		command->limiter_hd = next;
		command->limiter_hd->type = TOKEN_HEREDOC;
	}
	else if (token->type == TOKEN_REDIRECTION_APPEND_OUT)
	{
		command->outfile = next;
		command->outfile->type = TOKEN_REDIRECTION_APPEND_OUT;
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
