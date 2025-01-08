/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:38:55 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/08 13:34:21 by achantra         ###   ########.fr       */
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

short	parsing(t_minishell *env)
{
	if (get_input(env))
		return (1);
	//debug_print_input(env->input);
	if (handler_quote_expand(env, env->input))
		return (1);
	if (analyse_semantic(env))
		return (1);
	//debug_print_commands(env->cmds);
	return (0);
}
