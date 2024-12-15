/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:38:55 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/15 22:16:02 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	parsing(t_minishell *env)
{
	if (get_input(env))
		return (1);
	debug_print_input(env->input);
	if (analys_semantic(env))
		return (1);
	debug_print_commands(env->commands);
	delete_input(env);
	return (0);
}
