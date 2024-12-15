/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:34:25 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/15 00:52:22 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	is_sep(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

static size_t	handle_quotes(const char *str, size_t i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

static size_t	count_words(const char *str, char *sep)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], sep))
			i++;
		if (str[i] && !is_sep(str[i], sep))
		{
			w++;
			while (str[i] && !is_sep(str[i], sep))
			{
				if (str[i] == '"' || str[i] == '\'')
					i = handle_quotes(str, i);
				else
					i++;
			}
		}
	}
	return (w);
}

static char	*allocate_word(const char *str, char *sep)
{
	size_t	len;
	size_t	i;
	char	*w;

	len = 0;
	while (str[len] && !is_sep(str[len], sep))
	{
		if (str[len] == '"' || str[len] == '\'')
			len = handle_quotes(str, len);
		else
			len++;
	}
	w = malloc(sizeof(char) * (len + 1));
	if (!w)
		return (NULL);
	i = 0;
	while (i < len)
	{
		w[i] = str[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

static char	**split_words(char const *s, char *sep, char **tab)
{
	size_t	w;
	size_t	i;

	i = 0;
	w = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], sep))
			i++;
		if (s[i] && !is_sep(s[i], sep))
		{
			tab[w] = allocate_word(&s[i], sep);
			if (!tab[w])
			{
				while (w > 0)
					free(tab[--w]);
				free(tab);
				return (NULL);
			}
			w++;
			while (s[i] && !is_sep(s[i], sep))
			{
				if (s[i] == '"' || s[i] == '\'')
					i = handle_quotes(s, i);
				else
					i++;
			}
		}
	}
	return (tab);
}

char	**ft_split_minishell(char const *s, char *sep)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, sep) + 1));
	if (!tab)
		return (NULL);
	tab = split_words(s, sep, tab);
	if (!tab)
		return (NULL);
	tab[count_words(s, sep)] = NULL;
	return (tab);
}
