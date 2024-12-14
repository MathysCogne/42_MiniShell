/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:27:24 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 22:27:27 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Clean and free input and token after use
*/
void	ft_clean_input(t_minishell *env)
{
	t_input	*current;
	t_input	*next;

	current = env->input;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	env->input = NULL;
}
