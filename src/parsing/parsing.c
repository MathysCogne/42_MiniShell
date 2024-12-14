/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:38:55 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 22:43:56 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	parsing(t_minishell *env)
{
	if (ft_get_input(env))
		return (1);
	debug_print_input(env->input);
	ft_clean_input(env);
	return (0);
}
