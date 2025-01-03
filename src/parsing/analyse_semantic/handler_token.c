/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/03 00:49:48 by mcogne--         ###   ########.fr       */
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

// TODO: GERER LES LEAKS DE cmd_and_args du a (strjoin)
short	handler_argument(t_input *input, t_command *command)
{
	if (input->prev->token->type == TOKEN_PIPE)
		return (0);
	if (!command->cmd_and_args)
	{
		command->cmd_and_args = ft_strjoin(command->command->value, " ");
		command->cmd_and_args = ft_strjoin(command->cmd_and_args,
				input->token->value);
	}
	else
	{
		command->cmd_and_args = ft_strjoin(command->cmd_and_args, " ");
		command->cmd_and_args = ft_strjoin(command->cmd_and_args,
				input->token->value);
	}
	add_arg_command(input->token, command);
	return (0);
}
