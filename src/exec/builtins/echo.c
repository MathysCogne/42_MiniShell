/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:07:12 by achantra          #+#    #+#             */
/*   Updated: 2025/01/04 23:15:17 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **arg)
{
	int	i;
	int	optn;

	i = 1;
	optn = 0;
	if (arg[1] && !ft_strcmp(arg[1], "-n"))
	{
		optn = 1;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		i++;
		if (arg[i])
			ft_putchar_fd(' ', 1);
	}
	if (!optn)
		ft_putchar_fd('\n', 1);
	return (0);
}
