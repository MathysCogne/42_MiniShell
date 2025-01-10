/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:18:14 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 15:05:27 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_pwd(void)
{
	char	*pwd;
	char	*tmp1;
	char	*tmp2;

	pwd = getcwd(NULL, 0);
	tmp1 = ft_strjoin(YELLOW BOLD " [" C_RESET ITALIC "~", pwd);
	if (!tmp1)
		return (NULL);
	free(pwd);
	tmp2 = ft_strjoin(tmp1, YELLOW BOLD "] \n» " C_RESET);
	if (!tmp2)
	{
		free(tmp1);
		return (NULL);
	}
	free(tmp1);
	return (tmp2);
}

char	*get_shell_name(void)
{
	char	*shell_name;
	char	*current_pwd;
	char	*prompt;

	shell_name = YELLOW BOLD SHELL_NAME C_RESET;
	current_pwd = get_current_pwd();
	if (!current_pwd)
		return (NULL);
	prompt = ft_strjoin(shell_name, current_pwd);
	if (!prompt)
		return (NULL);
	free(current_pwd);
	return (prompt);
}
