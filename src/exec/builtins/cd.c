/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 02:16:35 by achantra          #+#    #+#             */
/*   Updated: 2025/01/07 17:49:43 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **args)
{
	char	*home;

	home = getenv("HOME");
	if (!args[1] || !ft_strcmp(args[1], "~"))
		chdir(home);
	else if (chdir(args[1]) == -1)
		return (ft_putstr_fd(SHELL_NAME_ERR, 2), ft_putstr_fd(" : cd: ", 2),
			perror(args[1]), 1);
	return (0);
}
