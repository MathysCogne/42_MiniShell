/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:59:31 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 12:26:10 by mcogne--         ###   ########.fr       */
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
	(void)env;
	if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIRECTION_IN);
	else if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIRECTION_OUT);
	else if (!ft_strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	else if (!ft_strcmp(token, ">>"))
		return (TOKEN_REDIRECTION_APPEND_OUT);
	else if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	else
		return (TOKEN_ARGUMENT);
}
