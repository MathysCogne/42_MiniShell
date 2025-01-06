/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:50:51 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 22:43:14 by mcogne--         ###   ########.fr       */
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

static void	print_args_command(t_command *command)
{
	size_t	i;

	i = 0;
	ft_printf("\t- args: [");
	while (command->args && command->args[i])
	{
		ft_printf("%s,", command->args[i]->value);
		i++;
	}
}

static void	print_command_details(t_command *command, int index)
{
	t_input	*input;

	input = command->redir_lst;
	ft_printf(RED "%d:" C_RESET, index);
	if (command->cmd)
		ft_printf("\t- cmd: %s \n\t- cmd->token->type: %s\n\t- cmd_path: %s\n",
			command->cmd->value, token_type_to_str(command->cmd->type),
			command->cmd_path);
	print_args_command(command);
	ft_printf("]\n\t- is_pipe: %d\n", command->is_pipe);
	ft_printf("\t- error_msg: %s\n", command->error_msg);
	ft_printf("\t- redir_lst:\n");
	while (input)
	{
		ft_printf("\t  -> Value: %s", input->token->value);
		ft_printf(" --> %s\n", token_type_to_str(input->token->type));
		input = input->next;
	}
	ft_printf("\n");
}

void	debug_print_commands(t_command *commands)
{
	size_t	i;

	i = 0;
	ft_printf(YELLOW "Commands List:\n" C_RESET);
	while (commands)
	{
		print_command_details(commands, i);
		commands = commands->next;
		i++;
	}
}

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
