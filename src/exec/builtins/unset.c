/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:17:42 by achantra          #+#    #+#             */
/*   Updated: 2025/01/10 10:32:57 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	realloc_del_env(char *arg, int indice)
{
	int			len;
	int			i;
    int         j;
	extern char	**environ;
	char		**new_environ;

	len = 0;
	while (environ && environ[len])
		len ++;
    if (len == 0)
        return (0);
	new_environ = malloc(sizeof(char *) * len);
	if (!new_environ)
		return (perror("malloc"), 2);
	new_environ[len - 1] = NULL;
	i = -1;
    j = 0;
	while (++i < len)
	{
        if (i != indice)
        {
            new_environ[j] = ft_strdup(environ[i]);
            if (!new_environ[j++])
                return (free_split(new_environ), 1);
        }
	}
	new_environ[len] = arg;
	free_split(environ);
	environ = new_environ;
	return (0);
}

int	del_key(t_minishell *env, char *arg, char *key)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(key, environ[i], ft_strlen(key))
			&& environ[i][ft_strlen(key)] == '=')
		{
            if (realloc_del_env(arg, i))
                return (2);
            break;
		}
		i++;
	}
	return (0);
}

int	del_env(t_minishell *env, char *arg)
{
	char	*key;
	char	*p_eq;

	p_eq = ft_strchr(arg, '=');
	if (p_eq)
	{
		key = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(p_eq));
		if (!key)
			return (2);
	}
	else
	{
		key = ft_strdup(arg);
		if (!key)
			return (2);
	}
	if (del_key(env, arg, key))
		return (2);
	return (free(key), 0);
}

int unset(t_minishell *env, char **arg)
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
		if (del_env(env, arg[i]))
			return (perror("malloc"), 2);
		i++;
	}
    return (0);
}