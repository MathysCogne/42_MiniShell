/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:35 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 14:46:00 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short	minishell(t_minishell *env)
{
	while (1)
	{
		if (ft_get_input(env))
			return (1);
		debug_print_input(env->input);
		ft_clean_input(env);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_minishell	env;

	if (argc != 1)
	{
		ft_printf("Usage: %s\n", argv[0]);
		return (1);
	}
	if (init_struct_env(&env))
		return (1);
	if (minishell(&env))
	{
		ft_printf("DEBUG: EXIT IN MAIN\n");
		gc_clean(env.gc);
		if (env.input)
			ft_clean_input(&env);
		return (1);
	}
	return (0);
}
