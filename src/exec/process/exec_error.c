/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:39:46 by achantra          #+#    #+#             */
/*   Updated: 2025/01/04 23:21:19 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pr_error(int e, char *element)
{
	if (e == PERM_ERROR || e == PERM_ERROR_END)
		ft_fprintf(2, "%s: %s: permission denied\n", get_shell_name(), element);
	else if (e == NOT_FOUND_ERROR)
		ft_fprintf(2, "%s: %s: command not found\n", get_shell_name(), element);
	else if (e == NO_PATH)
		ft_fprintf(2, "%s: no path in envp\n", get_shell_name());
	else if (e == NO_FILE)
		ft_fprintf(2, "%s: %s: no such file or directory\n", get_shell_name(),
			element);
	else if (e == EOF_HERE)
	{
		// line a revoir
		ft_fprintf(2,
			"%s: warning: here-document delimited by end-of-file (wanted '%s')\n",
			get_shell_name(), element);
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
