/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last_err_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:39:12 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/07 18:40:26 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	expand_last_err_code(t_minishell *env, char *var)
{
	char	*var_expand;
	char	*tmp;

	free(var);
	tmp = ft_itoa(env->last_err_code);
	var_expand = ft_strdup(tmp);
	free(tmp);
	return (var_expand);
}
