/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:22:56 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/07 17:23:19 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	handler_expand(t_minishell *env, t_token *token)
{
	char	*new_token;

	if (ft_strlen(token->value) < 2)
		return (0);
	new_token = expand_var(env, token);
	if (!new_token)
		return (1);
	free(token->value);
	token->value = new_token;
	return (0);
}

short	handler_quote_expand(t_minishell *env, t_input *input)
{
	short	quote_code;
	t_token	*token;

	while (input)
	{
		token = input->token;
		if (token->value[0] != '"' && token->value[0] != '\'')
		{
			if (handler_expand(env, token))
				return (1);
		}
		quote_code = handler_quote(token);
		if (quote_code == 1)
			return (1);
		if (quote_code == -1)
			handler_expand(env, token);
		if (delete_anti_slash(token))
			return (1);
		input = input->next;
	}
	return (0);
}
