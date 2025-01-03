/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:38:55 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/03 01:04:38 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	parsing(t_minishell *env)
{
	if (get_input(env))
		return (1);
	debug_print_input(env->input);
	if (analyse_semantic(env))
		return (1);
	debug_print_commands(env->commands);
	return (0);
}
