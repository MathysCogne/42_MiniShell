/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:35:40 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 14:45:39 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_add_back(t_input **input, t_input *new)
{
	t_input	*tmp;

	if (!input || !new)
		return ;
	if (*input == NULL)
	{
		*input = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = *input;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}
