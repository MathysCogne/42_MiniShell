/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:04:51 by achantra          #+#    #+#             */
/*   Updated: 2025/01/09 01:20:52 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Coucou,
// Tous les trois git que j'ai ete voir
// On une liste dans env, qui est une copie de l'environnement
// Et il utilise ca, apres du coup c'est pas vrm export vu que c'est pas 
// Accecible dans les autres environnements que notre shell,
// Donc pour moi c'est clairement de la triche de faire cela
// Et pareil pour unset du coup

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
