/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tmp_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:24:19 by achantra          #+#    #+#             */
/*   Updated: 2025/01/03 22:35:45 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*test_path(char **tab, char *cmd, int *error)
{
	int		i;
	char	*tmp;
	char	*path;

	if (*error == PERM_ERROR_END)
		return (pr_error(*error, cmd), NULL);
	i = -1;
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		if (!tmp)
			return (free_split(tab), perror(SHELL_NAME), NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (free_split(tab), perror(SHELL_NAME), NULL);
		if (test_input(path, error))
			return (free_split(tab), path);
		free(path);
	}
	if (*error == -1)
		*error = NOT_FOUND_ERROR;
	return (pr_error(*error, cmd), free_split(tab), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**tab;
	char	*path;
	int		i;
	int		error;

	error = -1;
	if (ft_strchr(cmd, '/') && test_input(cmd, &error))
	{
		path = ft_strdup(cmd);
		if (!path)
			return (perror(SHELL_NAME), NULL);
		return (path);
	}
	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tab = ft_split(envp[i] + 5, ':');
			if (!tab)
				return (perror(SHELL_NAME), NULL);
			return (test_path(tab, cmd, &error));
		}
	}
	return (pr_error(NO_PATH, NULL), NULL);
}

char	**split_arg(char *input)
{
	char	**arg;
	char	*tmp;
	int		i;

	if (ft_strrchr(input, '\''))
		arg = ft_split(input, '\'');
	else if (ft_strrchr(input, '"'))
		arg = ft_split(input, '"');
	else
		arg = ft_split(input, ' ');
	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		tmp = arg[i];
		arg[i] = ft_strtrim(arg[i], " \'\"");
		free(tmp);
		if (!arg[i])
			return (free_split(arg), NULL);
		i++;
	}
	return (arg);
}

int	find_cmd(t_command *cmd, char **envp)
{
	if (access(cmd->exec_args, F_OK) == 0 && ft_strchr(cmd->exec_args, '/'))
		cmd->exec_args2 = ft_split(cmd->exec_args, '\0');
	else
		cmd->exec_args2 = split_arg(cmd->exec_args);
	if (!cmd->exec_args2)
		return (perror(SHELL_NAME), 2);
	cmd->cmd_path = find_path(cmd->exec_args2[0], envp);
	return (0);
}
