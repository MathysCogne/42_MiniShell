/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:31:42 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 10:50:38 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	is_redir(char const *s, size_t i)
{
	if (i >= ft_strlen(s))
		return (0);
	if (s[i] == '|')
		return (1);
	if (i == 0)
	{
		if (s[i] == '>' || s[i] == '<')
			return (1);
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<'
				&& s[i + 1] == '<'))
			return (1);
	}
	if (i < ft_strlen(s))
	{
		if ((s[i] == '>' && i > 0 && s[i - 1] != '\\') || (s[i] == '<' && i > 0
				&& s[i - 1] != '\\'))
			return (1);
		if ((s[i] == '>' && s[i + 1] == '>' && s[i - 1] != '\\')
			|| (s[i] == '<' && s[i + 1] == '<' && s[i - 1] != '\\'))
			return (1);
	}
	return (0);
}

size_t	skip_redir(const char *str, size_t i)
{
	while (str[i] && is_redir(str, i))
		i++;
	return (i);
}

size_t	get_redir_len(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && is_redir(str, len))
		len++;
	return (len);
}
