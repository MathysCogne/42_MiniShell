/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:20:47 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 10:49:53 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Multiple redir
** No arguments for redir
*/
static short	validate_redirection_token(t_minishell *env, t_input *input,
		t_token *prev_token, t_command *command)
{
	(void)command;
	(void)prev_token;
	if (!input->next || input->next->token->type != TOKEN_ARGUMENT)
	{
		env->error_msg = ft_strdup(ERR_SYNTAX "`newline'");
		return (1);
	}
	if (input->next && input->next->token->type >= TOKEN_REDIRECTION_IN
		&& input->next->token->type <= TOKEN_REDIRECTION_APPEND_OUT)
	{
		env->error_msg = ft_strdup(ERR_SYNTAX "`newline'");
		return (1);
	}
	return (0);
}

/*
** Redirection before the pipe
** No command after the pipe
** Two pipes
*/
static short	validate_pipe_token(t_minishell *env, t_input *input,
		t_token *prev_token, t_command *command)
{
	(void)command;
	(void)prev_token;
	if (!input->next || (input->next->token->type != TOKEN_ARGUMENT))
	{
		env->error_msg = ft_strdup(ERR_SYNTAX "token `|'");
		return (1);
	}
	if (input->next && input->next->token->type == TOKEN_PIPE)
	{
		env->error_msg = ft_strdup(ERR_SYNTAX "token `|'");
		return (1);
	}
	return (0);
}

short	handler_validate_command(t_minishell *env, t_input *input,
		t_command *command)
{
	t_token	*prev_token;
	t_token	*token;

	prev_token = NULL;
	if (input->prev)
		prev_token = input->prev->token;
	if (env->error_msg)
		return (0);
	while (input)
	{
		token = input->token;
		if (token->type >= TOKEN_REDIRECTION_IN
			&& token->type <= TOKEN_REDIRECTION_APPEND_OUT
			&& validate_redirection_token(env, input, prev_token, command))
			break ;
		else if (token->type == TOKEN_PIPE)
		{
			return (validate_pipe_token(env, input, prev_token, command), 0);
		}
		prev_token = token;
		input = input->next;
	}
	return (0);
}
