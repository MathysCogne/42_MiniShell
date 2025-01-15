/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 02:02:39 by achantra          #+#    #+#             */
/*   Updated: 2025/01/13 17:18:52 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_b(int fd_out)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_putstr_fd(SHELL_NAME, 2), perror(": pwd: getcwd"), fd_out);
	ft_putendl_fd(cwd, fd_out);
	free(cwd);
	return (0);
}
