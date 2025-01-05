/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:35 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/05 01:31:49 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	minishell(t_minishell *env)
{
	setup_signal();
	while (1)
	{
		if (parsing(env))
		{
			ft_printf(RED "DEBUG: Exit in parsing part\n" C_RESET);
			return (1);
		}
		env->last_fd0 = 0;
		
		// if (exec(env))
		// {
		// 	ft_printf(RED "DEBUG: Exit in exec part\n" C_RESET);
		// 	return (1);
		// }
		delete_input(env);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	env;

	(void)envp;
	if (argc != 1)
	{
		ft_fprintf(2, RED BOLD "Usage: %s\n" C_RESET, argv[0]);
		return (1);
	}
	if (init_struct_env(&env))
		return (1);
	if (minishell(&env))
	{
		ft_fprintf(2, "exit\n");
		gc_clean(env.gc);
		if (env.input)
			delete_input(&env);
		return (1);
	}
	gc_clean(env.gc);
	if (env.input)
		delete_input(&env);
	return (0);
}
