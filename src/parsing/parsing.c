/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:38:55 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 10:53:00 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
| Welcome to the hell (..parsing, sorry) part 👋
|
├── analyse_semantic/
│	├── Processes tokens into structured commands
|
├── tokenization/
│	├── Splits input into tokens (args, pipes or redirections).
|
├── quote_expand/
│	├── Handles variable expansion and quote management.
|
├── utils/
│	├── Helper functions
*/

// For debug token add at line 36: debug_print_input(env->input);
// For debug commands add at line 42: debug_print_commands(env->cmds);
short	parsing(t_minishell *env)
{
	if (get_input(env))
		return (1);
	if (handler_quote_expand(env, env->input))
		return (1);
	if (analyse_semantic(env))
		return (1);
	return (0);
}
