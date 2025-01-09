/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 02:16:35 by achantra          #+#    #+#             */
/*   Updated: 2025/01/09 15:55:51 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **args)
{
	if (!args[1])
		return (ft_putstr_fd(SHELL_NAME, 2),
			ft_putendl_fd(" : cd: missing argument", 2), 1);
	else if (!ft_strlen(args[1]))
		return (0);
	else if (chdir(args[1]) == -1)
		return (ft_putstr_fd(SHELL_NAME, 2), ft_putstr_fd(" : cd: ", 2),
			perror(args[1]), 1);
	return (0);
}
