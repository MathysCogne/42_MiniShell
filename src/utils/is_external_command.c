/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_external_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:18:43 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 04:59:03 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Return tab** ENV PATH
** Warning: Free split tab ** after use
*/
static char	**get_paths_from_env(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	return (ft_split_minishell(path_env, ":"));
}

/*
** Return relatif path of command
** Warning: Free return after use
*/
static char	*join_path_and_command(const char *path, const char *command)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, command);
	free(tmp);
	return (cmd_path);
}

/*
** Return if valid and executable command
*/
// TODO ERREUR GESTION DES DROITS ??
static char	*check_command_in_paths(t_minishell *env, char **paths,
		const char *command)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_path_and_command(paths[i], command);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
		{
			gc_add(env->gc, cmd_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static char	*check_absolute_or_relative_path(t_minishell *env,
		const char *command)
{
	char	*cmd_path;

	if (access(command, X_OK) == 0)
	{
		cmd_path = strdup(command);
		if (!cmd_path)
			return (NULL);
		gc_add(env->gc, cmd_path);
		return (cmd_path);
	}
	return (NULL);
}

/*
** Check if external commands
*/
char	*is_external_command(t_minishell *env, char *token)
{
	char	**paths;
	char	*path_cmd;

	if (!token || !token[0])
		return (0);
	path_cmd = NULL;
	if (token[0] == '/' || ft_strncmp(token, "./", 2) == 0 || ft_strncmp(token,
			"../", 3) == 0)
	{
		path_cmd = check_absolute_or_relative_path(env, token);
		if (path_cmd)
			return (path_cmd);
	}
	paths = get_paths_from_env();
	if (!paths)
		return (0);
	path_cmd = check_command_in_paths(env, paths, token);
	env->envp = paths;
	return (path_cmd);
}
