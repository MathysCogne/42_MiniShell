/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:09:07 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 14:44:57 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	add_token(t_minishell *env, char *value, t_token_type type, size_t pos)
{
	t_token	*new_token;
	t_input	*new_input;

	new_token = create_token(env, value, type);
	if (!new_token)
		return (1);
	new_input = create_input(env, new_token, pos);
	if (!new_input)
		return (1);
	input_add_back(&env->input, new_input);
	return (0);
}

static short	parse_token(t_minishell *env, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (add_token(env, tab[i], TOKEN_COMMAND, i))
			return (1);
		i++;
	}
	return (0);
}

short	ft_get_input(t_minishell *env)
{
	char	*input;
	char	**tab_input;

	input = readline(CYAN SHELL_NAME C_RESET);
	if (!input)
		return (1);
	gc_add(env->gc, input);
	tab_input = ft_split_sep(input, TOKEN_SEPARATOR);
	if (parse_token(env, tab_input))
		return (1);
	return (0);
}
