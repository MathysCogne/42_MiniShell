/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:28:09 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 22:30:50 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add value of token
*/
void	input_add_back(t_input **input, t_input *new)
{
	t_input	*tmp;

	if (!input || !new)
		return ;
	if (*input == NULL)
	{
		*input = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = *input;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}

/*
** Init node of token
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
** Init node of input
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
** Manage put token
** Create Node token and input before add
*/
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
