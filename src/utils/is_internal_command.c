/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_internal_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:21:00 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 16:08:03 by achantra         ###   ########.fr       */
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
		NULL};
	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(token, builtin[i]))
			return (1);
		i++;
	}
	return (0);
}
