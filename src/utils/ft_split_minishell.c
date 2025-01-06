/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:34:25 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 20:35:49 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	is_redir(char const *s, size_t i)
{
	if (i >= ft_strlen(s))
		return (0);
	if (i == 0)
	{
		if (s[i] == '>' || s[i] == '<')
			return (1);
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i
				+ 1] == '<'))
			return (1);
	}
	if (i < ft_strlen(s))
	{
		if ((s[i] == '>' && i > 0 && s[i - 1] != '\\') || (s[i] == '<' && i > 0
				&& s[i - 1] != '\\'))
			return (1);
		if ((s[i] == '>' && s[i + 1] == '>' && s[i - 1] != '\\') || (s[i] == '<'
				&& s[i + 1] == '<' && s[i - 1] != '\\'))
			return (1);
	}
	return (0);
}

static char	**free_error_alloc(size_t i, char **tab)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
	return (NULL);
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
		if (str[i])
		{
			if (is_redir(str, i))
			{
				w++;
				while (str[i] && is_redir(str, i))
					i++;
			}
			else
			{
				w++;
				while (str[i] && !is_sep(str[i], sep) && !is_redir(str, i))
				{
					if (is_quote(str, i))
						i = handle_quotes(str, i);
					else
						i++;
				}
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
	if (is_redir(str, 0))
	{
		while (str[len] && is_redir(str, len))
			len++;
	}
	else
	{
		while (str[len] && !is_sep(str[len], sep) && !is_redir(str, len))
		{
			if (is_quote(str, len))
				len = handle_quotes(str, len);
			else
				len++;
		}
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
		if (s[i])
		{
			if (is_redir(&s[i], 0))
			{
				tab[w] = allocate_word(&s[i], sep);
				if (!tab[w])
					return (free_error_alloc(w, tab));
				w++;
				while (s[i] && is_redir(&s[i], 0))
					i++;
			}
			else
			{
				tab[w] = allocate_word(&s[i], sep);
				if (!tab[w])
					return (free_error_alloc(w, tab));
				w++;
				while (s[i] && !is_sep(s[i], sep) && !is_redir(&s[i], 0))
				{
					if (is_quote(s, i))
						i = handle_quotes(s, i);
					else
						i++;
				}
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
