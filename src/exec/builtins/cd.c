/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 02:16:35 by achantra          #+#    #+#             */
/*   Updated: 2025/01/06 22:51:31 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **args)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	home = getenv("HOME");
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd"), 1);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		chdir(home);
	// A revoir ici
	else if (chdir(args[1]) == -1)
		return (perror(args[1]), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("cd"), 1);
	// Recoder setenv car pas dans les fonctions autorisees
	setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", pwd, 1);
	free(oldpwd);
	free(pwd);
	return (0);
}
