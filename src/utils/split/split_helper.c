/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:32:38 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 22:44:28 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**free_error_alloc(size_t i, char **tab)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
	return (NULL);
}

size_t	skip_word(const char *str, size_t i, char *sep)
{
	while (str[i] && !is_sep(str[i], sep) && !is_redir(str, i))
	{
		if (is_quote(str, i))
			i = handle_quotes(str, i);
		else
			i++;
	}
	return (i);
}

size_t	get_word_len(const char *str, char *sep)
{
	size_t	len;

	len = 0;
	while (str[len] && !is_sep(str[len], sep) && !is_redir(str, len))
	{
		if (is_quote(str, len))
			len = handle_quotes(str, len);
		else
			len++;
	}
	return (len);
}
