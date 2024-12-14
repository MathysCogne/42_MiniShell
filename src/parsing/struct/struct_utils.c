/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 07:27:48 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 14:44:04 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Malloc and init node of token
*/
t_token	*create_token(t_minishell *env, char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	gc_add(env->gc, new_token);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

/*
** Malloc and init node of input
**
*/
t_input	*create_input(t_minishell *env, t_token *token, size_t pos)
{
	t_input	*new_input;

	new_input = malloc(sizeof(t_input));
	if (!new_input)
		return (NULL);
	gc_add(env->gc, new_input);
	new_input->token = token;
	new_input->pos = pos;
	return (new_input);
}

/*
** Init Garbage Colec
** Set Null INPUT
*/
short	init_struct_env(t_minishell *env)
{
	env->gc = gc_init();
	if (!env->gc)
		return (1);
	env->input = NULL;
	return (0);
}
