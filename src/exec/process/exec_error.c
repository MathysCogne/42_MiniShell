/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:39:46 by achantra          #+#    #+#             */
/*   Updated: 2025/01/07 17:50:56 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pr_error2(int e, char *element)
{
	if (e == NO_FILE)
	{
		ft_putstr_fd(SHELL_NAME_ERR, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	else if (e == EOF_HERE)
	{
		ft_putstr_fd(SHELL_NAME_ERR, 2);
		ft_putstr_fd(": warning: here-document delimited", 2);
		ft_putstr_fd(" by end-of-file (wanted '", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd("')\n", 2);
	}
}

void	pr_error(int e, char *element)
{
	if (e == PERM_ERROR || e == PERM_ERROR_END)
	{
		ft_putstr_fd(SHELL_NAME_ERR, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else if (e == NOT_FOUND_ERROR)
	{
		ft_putstr_fd(SHELL_NAME_ERR, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (e == NO_PATH)
	{
		ft_putstr_fd(SHELL_NAME_ERR, 2);
		ft_putstr_fd(": no path in envp\n", 2);
	}
	else
		pr_error2(e, element);
}
