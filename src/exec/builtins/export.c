/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:04:51 by achantra          #+#    #+#             */
/*   Updated: 2025/01/10 09:58:16 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		i++;
	}
	new_environ[len] = arg;
	free_split(environ);
	environ = new_environ;
	return (0);
}

int	find_key(char *arg, char **key)
{
	char	*p_eq;

	p_eq = ft_strchr(arg, '=');
	if (p_eq)
	{
		*key = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(p_eq));
		if (!*key)
			return (2);
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
			return (2);
	}
	return (0);
}

int	ft_setenv(t_minishell *env, char *arg)
{
	int			i;
	char		*key;
	extern char	**environ;

	if (find_key(arg, &key))
		return (2);
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(key, environ[i], ft_strlen(key))
			&& environ[i][ft_strlen(key)] == '=')
		{
			if (env->env_alloc)
				free(environ[i]);
			environ[i] = ft_strdup(arg);
			if (!environ[i])
				return (free(key), 2);
			break ;
		}
		i++;
	}
	if (!environ[i])
	{
		if (realloc_env(arg))
			return (free(key), 2);
	}
	return (free(key), 0);
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
		i++;
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
			export_error(arg[i]);
		}
		else if (ft_setenv(env, arg[i]))
			return (perror("malloc"), 2);
		i++;
	}
	return (status);
}
