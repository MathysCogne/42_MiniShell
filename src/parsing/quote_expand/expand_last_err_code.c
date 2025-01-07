/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last_err_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:39:12 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/07 21:21:33 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_last_err_code(t_minishell *env, char *var)
{
	int		code_sig;
	char	*var_expand;

	free(var);
	if (WIFSIGNALED(env->last_err_code))
	{
		code_sig = WTERMSIG(env->last_err_code);
		var_expand = ft_itoa(128 + code_sig);
	}
	else
		var_expand = ft_itoa(WEXITSTATUS(env->last_err_code));
	return (var_expand);
}
