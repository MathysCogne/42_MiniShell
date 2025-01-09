/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:29:11 by achantra          #+#    #+#             */
/*   Updated: 2025/01/09 13:25:18 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_b(t_minishell *env)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		ft_putendl_fd(environ[i], 1);
		i++;
	}
	(void) env;
	return (0);
}
