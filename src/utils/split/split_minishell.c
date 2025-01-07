/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:34:25 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/07 16:32:34 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			w++;
			if (is_redir(str, i))
				i = skip_redir(str, i);
			else
				i = skip_word(str, i, sep);
		}
	}
	return (w);
}

static void	copy_word(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static char	*allocate_word(const char *str, char *sep)
{
	size_t	len;
	char	*w;

	if (is_redir(str, 0))
		len = get_redir_len(str);
	else
		len = get_word_len(str, sep);
	w = malloc(sizeof(char) * (len + 1));
	if (!w)
		return (NULL);
	copy_word(w, str, len);
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
			tab[w] = allocate_word(&s[i], sep);
			if (!tab[w])
				return (free_error_alloc(w, tab));
			w++;
			if (is_redir(&s[i], 0))
				i = skip_redir(s, i);
			else
				i = skip_word(s, i, sep);
		}
	}
	return (tab);
}

char	**ft_split_minishell(char const *s, char *sep)
{
	char	**tab;

	if (!s || !s[0])
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
