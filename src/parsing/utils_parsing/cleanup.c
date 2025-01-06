/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:27:24 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 22:32:32 by mcogne--         ###   ########.fr       */
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
	env->cmds = NULL;
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
	free_split(env->envp);
	delete_commands(env);
	env->input = NULL;
}
