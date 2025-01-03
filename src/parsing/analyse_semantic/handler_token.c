/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/03 12:18:39 by achantra         ###   ########.fr       */
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
		command->outfile = next;
	else if (token->type == TOKEN_REDIRECTION_APPEND_OUT)
		command->outfile = next;
	return (0);
}

short	handler_pipe(t_input *input, t_command *command)
{
	if (!input->next)
		return (0);
	command->is_pipe = 1;
	return (0);
}

// TODO: GERER LES LEAKS DE exec_args du a (strjoin)
short	handler_argument(t_input *input, t_command *command)
{
	if (input->prev->token->type == TOKEN_PIPE)
		return (0);
	if (!command->exec_args)
	{
		command->exec_args = ft_strjoin(command->cmd->value, " ");
		command->exec_args = ft_strjoin(command->exec_args,
				input->token->value);
	}
	else
	{
		command->exec_args = ft_strjoin(command->exec_args, " ");
		command->exec_args = ft_strjoin(command->exec_args,
				input->token->value);
	}
	add_arg_command(input->token, command);
	return (0);
}
