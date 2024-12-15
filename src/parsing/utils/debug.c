/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:50:51 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/15 15:18:04 by mcogne--         ###   ########.fr       */
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

/*
** Print all tokens
*/
void	debug_print_input(t_input *input)
{
	ft_printf("====================\n");
	while (input)
	{
		ft_printf("Pos:   %d\n", input->pos);
		ft_printf("Value: %s\n", input->token->value);
		ft_printf("Token: %s\n", token_type_to_str(input->token->type));
		if (input->token->target_file)
			ft_printf("Target: %s\n", input->token->target_file);
		if (input->token->fd)
			ft_printf("FD: %d\n", input->token->fd);
		ft_printf("====================\n");
		input = input->next;
	}
}
