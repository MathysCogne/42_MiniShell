/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_quote_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:22:56 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 04:59:44 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *var)
{
	char	*var_expand;

	var_expand = getenv(var);
	free(var);
	if (!var_expand)
		return (ft_strdup(""));
	return (ft_strdup(var_expand));
}

char	*chr_var_to_expand(char *token)
{
	char	*var_expand;
	size_t	i;

	var_expand = ft_strchr(token, '$');
	if (!var_expand)
		return (ft_strdup(token));
	i = 0;
	while (var_expand[i] && var_expand[i] != ' ')
		i++;
	var_expand = strndup(var_expand + 1, i - 1);
	if (!var_expand)
		return (NULL);
	return (var_expand);
}

char	*replace_var_to_value(char *token, char *var_expand)
{
	char	*new_token;
	size_t	i;
	size_t	j;
	size_t	k;

	new_token = malloc(sizeof(char) * (ft_strlen(token) + ft_strlen(var_expand)
				+ 1));
	if (!new_token)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (token[i] && token[i] != '$')
		new_token[k++] = token[i++];
	if (token[i] == '$')
	{
		while (var_expand[j])
			new_token[k++] = var_expand[j++];
	}
	while (token[i] && token[i] != ' ')
		i++;
	while (token[i])
		new_token[k++] = token[i++];
	new_token[k] = '\0';
	return (new_token);
}

char	*expand_var(t_token *token)
{
	char	*var_expand;
	char	*new_token;

	var_expand = chr_var_to_expand(token->value);
	if (!var_expand)
		return (NULL);
	var_expand = get_env_var(var_expand);
	if (!var_expand)
		return (NULL);
	else
		new_token = replace_var_to_value(token->value, var_expand);
	if (!new_token)
		return (NULL);
	free(var_expand);
	return (new_token);
}

short	handler_expand(t_token *token)
{
	char	*new_token;

	if (ft_strlen(token->value) < 2)
		return (0);
	new_token = expand_var(token);
	if (!new_token)
		return (1);
	free(token->value);
	token->value = new_token;
	return (0);
}

/*
** If return -1, handler expand because is double quote
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
		new_token = strndup(token->value + 1, len - 2);
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

short	handler_quote_expand(t_input *input)
{
	short	quote_code;
	t_token	*token;

	while (input)
	{
		token = input->token;
		if (token->value[0] != '"' && token->value[0] != '\'')
		{
			if (handler_expand(token))
				return (1);
		}
		quote_code = handler_quote(token);
		if (quote_code == 1)
			return (1);
		if (quote_code == -1)
			handler_expand(token);
		input = input->next;
	}
	return (0);
}
