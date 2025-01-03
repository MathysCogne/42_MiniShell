/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:59:31 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/03 18:27:17 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Return type of token
**	0: Builtin / Internal command
**	1: External command
**	2: Argument
**	3: Redirection in ("<")
**	4: Redirection out (">")
**	5: Heredoc ("<<")
**	6: Redirection append out (">>")
**	7: Pipe ("|")
*/
t_token_type	tokenization(t_minishell *env, char *token)
{
	if (is_internal_command(token))
		return (TOKEN_BUILTIN);
	else if (is_external_command(env, token))
		return (TOKEN_COMMAND);
	else if (!strcmp(token, "<"))
		return (TOKEN_REDIRECTION_IN);
	else if (!strcmp(token, ">"))
		return (TOKEN_REDIRECTION_OUT);
	else if (!strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	else if (!strcmp(token, ">>"))
		return (TOKEN_REDIRECTION_APPEND_OUT);
	else if (!strcmp(token, "|"))
		return (TOKEN_PIPE);
	else
		return (TOKEN_ARGUMENT);
}
