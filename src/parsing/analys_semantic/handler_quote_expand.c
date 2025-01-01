/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_quote_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:22:56 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/01 23:54:43 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	handler_expand(t_token *token, t_command *command)
{
	(void)token;
	(void)command;
	return (0);
}

/*
** If return -1, handler expand because is double quote
*/
short	handler_quote(t_token *token, t_command *command)
{
	(void)token;
	(void)command;
	return (0);
}

short	handler_quote_expand(t_token *token, t_command *command)
{
	short	quote_code;

	quote_code = handler_quote(token, command);
	if (quote_code == 1)
		return (1);
	if (quote_code == -1)
		handler_expand(token, command);
	return (0);
}
