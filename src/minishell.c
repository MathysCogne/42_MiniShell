/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:35 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 05:20:53 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	minishell(void)
{
	char	*input;

	while (1)
	{
		input = readline(CYAN "bzh » " C_RESET);
		ft_printf("%s\n", input);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (1);
	minishell();
	return (0);
}
