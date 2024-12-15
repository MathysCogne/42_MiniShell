/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:32:41 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/15 16:34:35 by mcogne--         ###   ########.fr       */
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
	env->commands = NULL;
	return (0);
}
