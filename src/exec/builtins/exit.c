/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:21:37 by achantra          #+#    #+#             */
/*   Updated: 2025/01/08 14:34:43 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumeric(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_b(t_minishell *env, char **arg)
{
	int	exit_status;

	if (!arg[1])
		exit_status = env->last_err_code;
	else if (!ft_isnumeric(arg[1]))
	{
		ft_putstr_fd(SHELL_NAME_ERR, 2);
		ft_putstr_fd(": exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (1);
	}
	else if (arg[2])
	{
		ft_putstr_fd(SHELL_NAME_ERR, 2);
		ft_putendl_fd(": exit: too many arguments", 2);
		return (1);
	}
	else
		exit_status = ft_atoi(arg[1]);
	clean_child(env);
	exit(exit_status);
}
