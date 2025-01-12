/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last_err_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:39:12 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/12 22:25:13 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_last_err_code(t_minishell *env, char *var)
{
	char	*var_expand;
	int		exit_code;
	int		sig;

	free(var);
	if (!env->is_child)
		return (ft_itoa(env->last_err_code));
	if (WIFSIGNALED(env->last_err_code))
	{
		sig = WTERMSIG(env->last_err_code);
		if (sig == SIGQUIT)
			var_expand = ft_strdup("131");
		else
			var_expand = ft_strdup("130");
	}
	else if (WIFEXITED(env->last_err_code))
	{
		exit_code = WEXITSTATUS(env->last_err_code);
		var_expand = ft_itoa(exit_code);
	}
	else
		var_expand = ft_strdup("1");
	return (var_expand);
}
