/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:17:42 by achantra          #+#    #+#             */
/*   Updated: 2025/01/10 11:31:54 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_new_environ(char **new_environ, int len, int indice)
{
	int			i;
	int			j;
	extern char	**environ;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (i != indice)
		{
			new_environ[j] = ft_strdup(environ[i]);
			if (!new_environ[j])
				return (free_split(new_environ), 1);
			j++;
		}
		i++;
	}
	free_split(environ);
	environ = new_environ;
	return (0);
}

static int	realloc_del_env(int indice)
{
	int			len;
	extern char	**environ;
	char		**new_environ;

	len = 0;
	while (environ && environ[len])
		len++;
	if (len == 0)
		return (0);
	new_environ = malloc(sizeof(char *) * len);
	if (!new_environ)
		return (perror("malloc"), 2);
	new_environ[len - 1] = NULL;
	if (set_new_environ(new_environ, len, indice))
		return (perror("malloc"), 2);
	return (0);
}

static int	del_key(char *key)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(key, environ[i], ft_strlen(key))
			&& environ[i][ft_strlen(key)] == '=')
		{
			if (realloc_del_env(i))
				return (2);
			break ;
		}
		i++;
	}
	return (0);
}

int	unset_b(t_minishell *env, char **arg)
{
	int	i;

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
		if (del_key(arg[i]))
			return (perror("malloc"), 2);
		i++;
	}
	return (0);
}
