/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_external_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:18:43 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/15 00:42:33 by mcogne--         ###   ########.fr       */
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
static short	check_command_in_paths(char **paths, const char *command)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_path_and_command(paths[i], command);
		if (!cmd_path)
			return (0);
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd_path);
			return (1);
		}
		free(cmd_path);
		i++;
	}
	return (0);
}

/*
** Check if external commands
*/
short	is_external_command(char *token)
{
	char	**paths;
	int		is_command_found;

	paths = get_paths_from_env();
	if (!paths)
		return (0);
	is_command_found = check_command_in_paths(paths, token);
	free_split(paths);
	return (is_command_found);
}
