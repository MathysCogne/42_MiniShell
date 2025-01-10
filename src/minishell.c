/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:35 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 10:51:32 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	minishell(t_minishell *env)
{
	setup_signal();
	while (1)
	{
		if (parsing(env))
			return (1);
		if (env->cmds)
		{
			env->last_fd0 = 0;
			if (exec(env))
				return (1);
			if (WIFSIGNALED(env->last_err_code)
				&& WTERMSIG(env->last_err_code) == SIGQUIT)
				ft_fprintf(2, "\t%d quit (core dumped)\n", env->cmds->pid);
		}
		delete_input(env);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_minishell	env;

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
		clean_environ(&env);
		gc_clean(env.gc);
		if (env.input)
			delete_input(&env);
		return (1);
	}
	clean_environ(&env);
	gc_clean(env.gc);
	if (env.input)
		delete_input(&env);
	return (0);
}
