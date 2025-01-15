/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:09:17 by achantra          #+#    #+#             */
/*   Updated: 2025/01/13 18:11:36 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	f_fd_out(t_command *cmd)
{
	t_input	*last_input_out;
	t_input	*tmp;

	tmp = cmd->redir_lst;
	last_input_out = NULL;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_REDIRECTION_OUT
			|| tmp->token->type == TOKEN_REDIRECTION_APPEND_OUT)
			last_input_out = tmp;
		tmp = tmp->next;
	}
	if (last_input_out)
	{
		if (last_input_out->token->type == TOKEN_REDIRECTION_OUT)
			return (open(last_input_out->token->value,
					O_CREAT | O_WRONLY | O_TRUNC, 0644));
		else
			return (open(last_input_out->token->value,
					O_CREAT | O_WRONLY | O_APPEND, 0644));
	}
	else
		return (1);
}

int	check_redir(t_command *cmds)
{
	int	fd_out;

	if (open_redir(cmds))
		return (-1);
	fd_out = f_fd_out(cmds);
	if (fd_out < 0)
		perror(SHELL_NAME);
	return (fd_out);
}
