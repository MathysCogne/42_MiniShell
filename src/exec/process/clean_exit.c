/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:17:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/07 18:22:33 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc(t_command *cmd)
{
	t_input	*tmp;

	tmp = cmd->redir_lst;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_HEREDOC)
			unlink(tmp->token->value);
		tmp = tmp->next;
	}
}

void	clean_child(t_minishell *env)
{
	gc_clean(env->gc);
	delete_input(env);
}
