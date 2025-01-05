/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:36:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/05 01:01:19 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// short	put_input(t_minishell *env, char *value, t_token_type type)
// {
// 	t_token	*new_token;
// 	t_input	*new_input;

// 	new_token = create_token(value, type);
// 	if (!new_token)
// 		return (1);
// 	new_input = create_input(new_token);
// 	if (!new_input)
// 		return (1);
// 	input_add_back(&env->input, new_input);
// 	return (0);
// }

static short	put_input_redir(t_command *current_command, char *value,
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
		return (put_input_redir(command, next->value, TOKEN_REDIRECTION_IN));
	else if (token->type == TOKEN_REDIRECTION_OUT)
		return (put_input_redir(command, next->value, TOKEN_REDIRECTION_OUT));
	else if (token->type == TOKEN_HEREDOC)
		return (put_input_redir(command, next->value, TOKEN_HEREDOC));
	else if (token->type == TOKEN_REDIRECTION_APPEND_OUT)
		return (put_input_redir(command, next->value,
				TOKEN_REDIRECTION_APPEND_OUT));
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
