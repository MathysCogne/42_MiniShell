/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:31:18 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 22:50:33 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	is_quote(char const *s, size_t i)
{
	if (i == 0)
	{
		if (s[i] == '"' || s[i] == '\'')
			return (1);
	}
	if ((s[i] == '"' && s[i - 1] != '\\') || (s[i] == '\'' && s[i - 1] != '\\'))
		return (1);
	return (0);
}

size_t	handle_quotes(const char *str, size_t i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}
