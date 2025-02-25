/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:23:11 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 21:08:28 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Extract arg: token -to> char ** tab
** For exec
*/
short	extract_args(t_command *command)
{
	int		i;
	t_token	**args;

	i = 0;
	args = command->args;
	command->str_args = malloc(sizeof(char *) * (ft_tablen((void **)args) + 1));
	if (!command->str_args)
		return (1);
	while (args && args[i])
	{
		command->str_args[i] = args[i]->value;
		i++;
	}
	command->str_args[i] = NULL;
	return (0);
}
