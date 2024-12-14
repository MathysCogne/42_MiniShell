/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:50:51 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 14:38:24 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print all tokens
*/
void	debug_print_input(t_input *input)
{
	ft_printf("====================\n");
	while (input)
	{
		ft_printf("Position: %d\n", input->pos);
		ft_printf("Value: %s\n", input->token->value);
		ft_printf("Type: %d\n", input->token->type);
		ft_printf("====================\n");
		input = input->next;
	}
}
