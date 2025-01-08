/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:04:51 by achantra          #+#    #+#             */
/*   Updated: 2025/01/08 16:19:03 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(char *arg)
{
	extern char	**environ;
    char **env = environ;
	int			i;
	char		*key;
	char		*value;
	char		*p_eq;

	// Fonction a recoder
	p_eq = ft_strchr(arg, '=');
	if (p_eq)
	{
		key = strndup(arg, p_eq - arg);
		value = ft_strdup(p_eq + 1);
	}
	else
	{
		key = strdup(arg);
		value = NULL;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], ft_strlen(key))
			&& env[i][ft_strlen(key)] == '=')
        {
            ft_printf("%s\n", env[i]);
			free(env[i]);
            env[i] = ft_strjoin(key, p_eq);
        }
		i++;
	}
	if (key)
		free(key);
	if (value)
		free(value);
	return (0);
}

int	export_b(char **arg)
{
	int	i;
	int	err;

	err = 0;
    // Creuser ce qu'il faut afficher si pas d arguments
	if (!arg[1])
		return (0);
    //
	i = 1;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "="))
		{
			err = 1;
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putendl_fd(": export: '=': not valid identifier", 2);
		}
		else if (ft_setenv(arg[i]))
			err = 1;
		i++;
	}
	return (err);
}
