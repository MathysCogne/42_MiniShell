/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:27:24 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/13 15:56:42 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
	tab = NULL;
}

static void	delete_input_redir(t_input *input)
{
	t_input	*current;
	t_input	*next;

	current = input;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
}

static void	delete_commands(t_minishell *env)
{
	t_command	*current;
	t_command	*next;
	int			i;

	if (!env->cmds)
		return ;
	current = env->cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				i++;
			free(current->args);
		}
		delete_input_redir(current->redir_lst);
		if (current->error_msg)
			free(current->error_msg);
		if (current->str_args)
			free(current->str_args);
		free(current);
		current = next;
	}
}

static void	reset_input(t_minishell *env)
{
	env->input = NULL;
	env->cmds = NULL;
	env->envp = NULL;
	env->error_msg = NULL;
}

/*
** Clean and free input and token after use
*/
void	delete_input(t_minishell *env)
{
	t_input	*current;
	t_input	*next;

	current = env->input;
	while (current)
	{
		next = current->next;
		free(current->token->value);
		free(current->token);
		free(current);
		current = next;
	}
	if (env->envp)
		free_split(env->envp);
	if (env->error_msg)
		free(env->error_msg);
	delete_commands(env);
	reset_input(env);
}
