/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 02:02:39 by achantra          #+#    #+#             */
/*   Updated: 2025/01/06 02:10:20 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_b(void)
{
    char	*cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("pwd"), 1);
    ft_putendl_fd(cwd, 1);
    free(cwd);
    return (0);
}