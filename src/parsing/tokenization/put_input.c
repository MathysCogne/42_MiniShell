/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:28:09 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 21:19:26 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Manage put token
** Create Node token and input before add
*/
short	put_input(t_minishell *env, char *value, t_token_type type)
{
	t_token	*new_token;
	t_input	*new_input;

	new_token = create_token(value, type);
	if (!new_token)
		return (1);
	new_input = create_input(new_token);
	if (!new_input)
		return (1);
	input_add_back(&env->input, new_input);
	return (0);
}
