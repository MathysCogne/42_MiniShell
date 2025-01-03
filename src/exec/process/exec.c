/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:35:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/03 18:35:02 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_process(t_minishell *env, int *p_end)
{
	pid_t	pid;

	while (env->curr_cmd)
	{
		if (pipe(p_end) == -1)
			return (perror(SHELL_NAME), EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
		{
			if (env->last_fd0)
				close(env->last_fd0);
			return (close(p_end[0]), close(p_end[1]), perror(SHELL_NAME),
				EXIT_FAILURE);
		}
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

// UNLINK LES TMP

short	exec(t_minishell *env)
{
	int	p_end[2];
	int	status;

	// Probablement a deplacer dans le parsing
	find_heredoc(env->cmds);
	env->curr_cmd = env->cmds;
	// ---------
	if (main_process(env, p_end))
		return (EXIT_FAILURE);
	env->curr_cmd = env->cmds;
	while (env->curr_cmd)
	{
		waitpid(env->curr_cmd->pid, &status, 0);
		env->curr_cmd = env->curr_cmd->next;
	}
	env->last_err_code = WEXITSTATUS(status);
	return (close(p_end[0]), close(p_end[1]), 0);
}
