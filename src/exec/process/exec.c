/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:35:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/07 15:51:49 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_process_error(t_minishell *env, int *p_end)
{
	if (p_end)
	{
		close(p_end[0]);
		close(p_end[1]);
	}
	if (env->last_fd0)
		close(env->last_fd0);
	perror(get_shell_name());
	return (EXIT_FAILURE);
}

int	main_process(t_minishell *env, int *p_end)
{
	pid_t	pid;

	while (env->curr_cmd)
	{
		if (pipe(p_end) == -1)
			return (handle_process_error(env, NULL));
		pid = fork();
		if (pid < 0)
			return (handle_process_error(env, p_end));
		else if (pid == 0)
			exit(child_process(p_end, env, env->curr_cmd));
		else
		{
			env->curr_cmd->pid = pid;
			if (env->last_fd0)
				close(env->last_fd0);
			close(p_end[1]);
			env->last_fd0 = p_end[0];
		}
		env->curr_cmd = env->curr_cmd->next;
	}
	return (0);
}

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

short	exec(t_minishell *env)
{
	int	p_end[2];
	int	status;

	env->last_fd0 = 0;
	find_heredoc(env->cmds);
	env->curr_cmd = env->cmds;
	if (main_process(env, p_end))
		return (EXIT_FAILURE);
	env->curr_cmd = env->cmds;
	while (env->curr_cmd)
	{
		waitpid(env->curr_cmd->pid, &status, 0);
		clean_heredoc(env->curr_cmd);
		env->curr_cmd = env->curr_cmd->next;
	}
	env->last_err_code = WEXITSTATUS(status);
	return (close(p_end[0]), close(p_end[1]), 0);
}
