/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:39:46 by achantra          #+#    #+#             */
/*   Updated: 2025/01/04 18:56:42 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pr_error(int e, char *element)
{
	if (e == PERM_ERROR || e == PERM_ERROR_END)
		ft_fprintf(2, "%s: %s: permission denied\n", SHELL_NAME, element);
	else if (e == NOT_FOUND_ERROR)
		ft_fprintf(2, "%s: %s: command not found\n", SHELL_NAME, element);
	else if (e == NO_PATH)
		ft_fprintf(2, "%s: no path in envp\n", SHELL_NAME);
	else if (e == NO_FILE)
		ft_fprintf(2, "%s: %s: no such file or directory\n", SHELL_NAME,
			element);
	else if (e == EOF_HERE)
	{
		// line a revoir
		ft_fprintf(2,
		"%s: warning: here-document delimited by end-of-file (wanted '%s')\n",
		SHELL_NAME, element);
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
