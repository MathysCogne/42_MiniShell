/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:38:55 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 02:04:20 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	parsing(t_minishell *env)
{
	if (get_input(env))
		return (1);
	// debug_print_input(env->input);
	if (handler_quote_expand(env->input))
		return (1);
	if (analyse_semantic(env))
		return (1);
	// debug_print_commands(env->cmds);
	return (0);
}
