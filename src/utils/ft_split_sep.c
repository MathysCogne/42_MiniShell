/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:34:25 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 09:06:21 by mcogne--         ###   ########.fr       */
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

static size_t	c_w(const char *str, char *sep)
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
				i++;
		}
	}
	return (w);
}

static char	*malloc_worlds(const char *str, char *sep)
{
	size_t	len;
	size_t	i;
	char	*w;

	len = 0;
	while (str[len] && !is_sep(str[len], sep))
		len++;
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

static char	**worlds(char const *s, char *sep, char **tab)
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
			tab[w] = malloc_worlds(&s[i], sep);
			if (!tab[w])
			{
				free(tab[w]);
				while (--w != 0)
					free(tab[w]);
				return (NULL);
			}
			w++;
			while (s[i] && !is_sep(s[i], sep))
				i++;
		}
	}
	return (tab);
}

char	**ft_split_sep(char const *s, char *sep)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (c_w(s, sep) + 1));
	if (!tab)
		return (NULL);
	tab = worlds(s, sep, tab);
	if (!tab)
	{
		free(tab);
		return (NULL);
	}
	tab[c_w(s, sep)] = NULL;
	return (tab);
}
