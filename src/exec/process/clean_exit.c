/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:17:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/10 11:38:18 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc(t_minishell *env)
{
	t_command	*tmp_cmd;
	t_input		*tmp;

	tmp_cmd = env->cmds;
	while (tmp_cmd)
	{
		tmp = tmp_cmd->redir_lst;
		while (tmp)
		{
			if (tmp->token->type == TOKEN_HEREDOC)
				unlink(tmp->token->value);
			tmp = tmp->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}

void	clean_environ(t_minishell *env)
{
	extern char	**environ;

	if (env->env_alloc)
		free_split(environ);
	environ = NULL;
}

void	clean_child(t_minishell *env)
{
	clean_environ(env);
	clean_heredoc(env);
	gc_clean(env->gc);
	delete_input(env);
}
