/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:09:07 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/25 15:54:01 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	parse_token(t_minishell *env, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (put_input(env, tab[i], tokenization(tab[i])))
			return (1);
		i++;
	}
	gc_add(env->gc, tab[i]);
	gc_add(env->gc, tab);
	return (0);
}

/*
** Manage input user
** 	Get input user with readline
** 	Post input in hystory./
** 	Split input by token with separator
*/
short	get_input(t_minishell *env)
{
	char	*input;
	char	**tab_input;

	input = readline(CYAN SHELL_NAME C_RESET);
	if (!input)
		return (1);
	add_history(input);
	gc_add(env->gc, input);
	tab_input = ft_split_minishell(input, TOKEN_SEPARATOR);
	if (parse_token(env, tab_input))
		return (1);
	return (0);
}
