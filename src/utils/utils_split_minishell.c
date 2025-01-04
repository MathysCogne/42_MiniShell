/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:32:38 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 02:56:29 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

short	is_quote(char const *str, size_t i)
{
	if (!str[i - 1])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
	}
	else if ((str[i] == '"' && str[i - 1] != '\\') || (str[i] == '\'' && str[i
			- 1] != '\\'))
		return (1);
	return (0);
}

short	is_sep(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
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
