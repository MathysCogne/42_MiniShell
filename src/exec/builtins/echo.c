/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:07:12 by achantra          #+#    #+#             */
/*   Updated: 2025/01/13 17:20:58 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **arg, int fd_out)
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
		ft_putstr_fd(arg[i], fd_out);
		i++;
		if (arg[i])
			ft_putchar_fd(' ', fd_out);
	}
	if (!optn)
		ft_putchar_fd('\n', fd_out);
	return (0);
}
