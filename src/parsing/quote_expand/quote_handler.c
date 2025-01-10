/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:22:56 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 11:58:25 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if the token is quoted and remove the quotes
** Return -1 if the token is quoted with double quotes -> = Expand
*/
short	handler_quote(t_token *token)
{
	size_t	len;
	char	*new_token;

	len = ft_strlen(token->value);
	if (len < 2)
		return (0);
	if ((token->value[0] == '"' && token->value[len - 1] == '"')
		|| (token->value[0] == '\'' && token->value[len - 1] == '\''))
	{
		new_token = ft_strndup(token->value + 1, len - 2);
		if (!new_token)
			return (1);
		if (token->value[0] == '"')
		{
			free(token->value);
			token->value = new_token;
			return (-1);
		}
		free(token->value);
		token->value = new_token;
	}
	return (0);
}

short	delete_anti_slash(t_token *token)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\\' && (token->value[i + 1] == '\''
				|| token->value[i + 1] == '"'))
			i++;
		token->value[j] = token->value[i];
		i++;
		j++;
	}
	token->value[j] = '\0';
	return (0);
}
