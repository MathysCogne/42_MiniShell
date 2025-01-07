/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:29:11 by achantra          #+#    #+#             */
/*   Updated: 2025/01/06 22:51:35 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_b(void)
{
	int			i;
	extern char	**environ;

	// Checker si c est ok pour la norme
	i = 0;
	while (environ[i])
	{
		ft_putendl_fd(environ[i], 1);
		i++;
	}
	return (0);
}
