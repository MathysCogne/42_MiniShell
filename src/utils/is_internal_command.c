/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_internal_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:21:00 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/15 01:41:47 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if builtin commands
** echo - cd - pwd - export - unset - env - exit
*/
short	is_internal_command(char *token)
{
	char	**builtin;
	int		i;

	builtin = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit",
		"history", NULL};
	i = 0;
	while (builtin[i])
	{
		if (!strcmp(token, builtin[i]))
			return (1);
		i++;
	}
	return (0);
}
