/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:32:41 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/12 22:23:07 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Init env structure, and init gc
*/
short	init_struct_env(t_minishell *env)
{
	env->gc = gc_init();
	if (!env->gc)
		return (1);
	env->input = NULL;
	env->cmds = NULL;
	env->curr_cmd = NULL;
	env->last_err_code = 0;
	env->is_child = 1;
	env->envp = NULL;
	env->env_alloc = 0;
	env->last_fd0 = 0;
	env->error_msg = NULL;
	return (0);
}
