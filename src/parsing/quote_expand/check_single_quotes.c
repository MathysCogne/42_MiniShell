/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:38:45 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/07 16:21:16 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	check_single_quotes(char *str)
{
	size_t	i;
	size_t	count_simple;
	size_t	count_double;

	if (!str || !str[0])
		return (0);
	i = 0;
	count_simple = 0;
	count_double = 0;
	if (str[i] == '"')
		count_double++;
	else if (str[i] == '\'')
		count_simple++;
	i++;
	while (str[i])
	{
		if (str[i] == '"' && str[i - 1] != '\\')
			count_double++;
		else if (str[i] == '\'' && str[i - 1] != '\\')
			count_simple++;
		i++;
	}
	if (count_simple % 2 != 0 || count_double % 2 != 0)
		return (1);
	return (0);
}
