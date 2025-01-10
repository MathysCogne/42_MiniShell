/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:22:56 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 11:58:29 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(t_minishell *env, char *var)
{
	char	*var_expand;

	if (ft_strchr(var, '?'))
		return (expand_last_err_code(env, var));
	var_expand = getenv(var);
	free(var);
	if (!var_expand)
		return (ft_strdup(""));
	return (ft_strdup(var_expand));
}

static char	*chr_var_to_expand(char *token)
{
	char	*var_expand;
	size_t	i;

	var_expand = ft_strchr(token, '$');
	if (!var_expand)
		return (ft_strdup(token));
	i = 0;
	while (var_expand[i] && var_expand[i] != ' ')
		i++;
	var_expand = ft_strndup(var_expand + 1, i - 1);
	if (!var_expand)
		return (NULL);
	return (var_expand);
}

static char	*replace_var_to_value(char *token, char *var_expand)
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

char	*expand_var(t_minishell *env, t_token *token)
{
	char	*var_expand;
	char	*new_token;

	var_expand = chr_var_to_expand(token->value);
	if (!var_expand)
		return (NULL);
	var_expand = get_env_var(env, var_expand);
	if (!var_expand)
		return (NULL);
	else
		new_token = replace_var_to_value(token->value, var_expand);
	if (!new_token)
		return (NULL);
	free(var_expand);
	return (new_token);
}
