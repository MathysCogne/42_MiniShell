/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:18:14 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 01:01:59 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_dir(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (NULL);
	return (current_dir);
}

char	*get_shell_name(void)
{
	char	*shell_name;

	shell_name = CYAN SHELL_NAME C_RESET;
	return (shell_name);
}
