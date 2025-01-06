/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:39:46 by achantra          #+#    #+#             */
/*   Updated: 2025/01/06 00:59:40 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pr_error(int e, char *element)
{
	if (e == PERM_ERROR || e == PERM_ERROR_END)
	{
		ft_putstr_fd(get_shell_name(), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else if (e == NOT_FOUND_ERROR)
	{
		ft_putstr_fd(get_shell_name(), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (e == NO_PATH)
	{
		ft_putstr_fd(get_shell_name(), 2);
		ft_putstr_fd(": no path in envp\n", 2);
	}
	else if (e == NO_FILE)
	{
		ft_putstr_fd(get_shell_name(), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	else if (e == EOF_HERE)
	{
		ft_putstr_fd(get_shell_name(), 2);
		ft_putstr_fd(": warning: here-document delimited by end-of-file (wanted '", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd("')\n", 2);
	}
}

int	test_input(char *input, int *error)
{
	if (access(input, F_OK) == 0)
	{
		if (access(input, X_OK) == 0)
			return (1);
		else if (ft_strchr(input, '/'))
			*error = PERM_ERROR_END;
		else
			*error = PERM_ERROR;
	}
	return (0);
}
