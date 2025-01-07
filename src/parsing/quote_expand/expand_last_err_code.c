/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last_err_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:39:12 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/07 22:34:25 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_last_err_code(t_minishell *env, char *var)
{
	char	*var_expand;
	int		exit_code;

	free(var);
	if (WIFSIGNALED(env->last_err_code))
		var_expand = ft_strdup("130");
	else if (WIFEXITED(env->last_err_code))
	{
		exit_code = WEXITSTATUS(env->last_err_code);
		var_expand = ft_itoa(exit_code);
	}
	else
		var_expand = ft_strdup("1");
	return (var_expand);
}
