/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:50:51 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 15:29:19 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_type_to_str(t_token_type token)
{
	if (token == TOKEN_BUILTIN)
		return ("BUILTIN");
	else if (token == TOKEN_COMMAND)
		return ("COMMAND");
	else if (token == TOKEN_REDIRECTION_IN)
		return ("REDIRECTION_IN");
	else if (token == TOKEN_REDIRECTION_OUT)
		return ("REDIRECTION_OUT");
	else if (token == TOKEN_HEREDOC)
		return ("HEREDOC");
	else if (token == TOKEN_REDIRECTION_APPEND_OUT)
		return ("REDIRECTION_APPEND_OUT");
	else if (token == TOKEN_PIPE)
		return ("PIPE");
	else if (token == TOKEN_ARGUMENT)
		return ("ARGUMENT");
	else
		return ("Error: (Null)");
}

void	debug_print_commands(t_command *commands)
{
	int	i;
	int	j;

	i = 0;
	ft_printf(YELLOW "Commands List:\n" C_RESET);
	while (commands)
	{
		ft_printf(RED "%d:" C_RESET, i);
		if (commands->cmd)
			ft_printf("\t- cmd: %s \n\t- cmd->token->type: %s\n\t- cmd_path: %s\n",
				commands->cmd->value, token_type_to_str(commands->cmd->type), commands->cmd_path);
		ft_printf("\t- args: [");
		j = 0;
		while (commands->args && commands->args[j])
		{
			ft_printf("%s,", commands->args[j]->value);
			j++;
		}
		ft_printf("]\n\t- is_pipe: %d\n", commands->is_pipe);
		if (commands->outfile)
			ft_printf("\t- outfile: %s\n", commands->outfile->value);
		if (commands->infile)
			ft_printf("\t- infile: %s\n", commands->infile->value);
		if (commands->limiter_herdoc)
			ft_printf("\t- limiter_herdoc: %s\n",
				commands->limiter_herdoc->value);
		ft_printf("\t- error_msg: %s\n\n", commands->error_msg);
		commands = commands->next;
		i++;
	}
}

/*
** Print all tokens
*/
void	debug_print_input(t_input *input)
{
	ft_printf(YELLOW "Token List:\n" C_RESET);
	while (input)
	{
		ft_printf("- %s: ", token_type_to_str(input->token->type));
		ft_printf(GREEN "%s\n" C_RESET, input->token->value);
		input = input->next;
	}
	ft_printf("\n");
}
