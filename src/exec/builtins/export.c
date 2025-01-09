/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:04:51 by achantra          #+#    #+#             */
/*   Updated: 2025/01/09 16:58:10 by achantra         ###   ########.fr       */
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

int	realloc_env(char *arg)
{
	int			len;
	int			i;
	extern char	**environ;
	char		**new_environ;

	len = 0;
	while (environ && environ[len])
		len++;
	new_environ = malloc(sizeof(char *) * (len + 2));
	if (!new_environ)
		return (free(arg), perror("malloc"), 1);
	new_environ[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
			return (free(arg), free_split(new_environ), 1);
		i ++;
	}
	new_environ[len] = arg;
	free_split(environ);
	environ = new_environ;
	return (0);	
}

int	ft_setenv(t_minishell *env, char *arg)
{
	int			i;
	char		*key;
	char		*value;
	char		*p_eq;
	extern char	**environ;

	p_eq = ft_strchr(arg, '=');
	if (p_eq)
	{
		key = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(p_eq));
		value = ft_strdup(p_eq + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(key, environ[i], ft_strlen(key))
			&& environ[i][ft_strlen(key)] == '=')
		{
			if (env->env_alloc)
				free(environ[i]);
			environ[i] = ft_strjoin(key, p_eq);
			break;
		}
		i++;
	}
	if (!environ[i])
		realloc_env(ft_strjoin(key, p_eq));
	if (key)
		free(key);
	if (value)
		free(value);
	return (0);
}

int	alloc_env(t_minishell *env)
{
	int			len;
	int			i;
	extern char	**environ;
	char		**new_environ;

	len = 0;
	while (environ && environ[len])
		len++;
	new_environ = malloc(sizeof(char *) * (len + 1));
	if (!new_environ)
		return (perror("malloc"), 1);
	new_environ[len] = NULL;
	i = 0;
	while (i < len)
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
			return (free_split(new_environ), 1);
		i ++;
	}
	environ = new_environ;
	env->env_alloc = 1;
	return (0);
}

int	export_b(t_minishell *env, char **arg)
{
	int	i;
	int	status;

	status = 0;
	if (!arg[1])
		return (0);
	if (!env->env_alloc)
	{
		if (alloc_env(env))
			return (perror("malloc"), 2);
	}
	i = 1;
	while (arg[i])
	{
		if (arg[i][0] == '=')
		{
			status = 1;
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd(": export: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putendl_fd(": not valid identifier", 2);
		}
		else if (ft_setenv(env, arg[i]))
			status = 1;
		i++;
	}
	return (status);
}
