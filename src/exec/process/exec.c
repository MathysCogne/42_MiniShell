/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:35:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/04 23:21:19 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_process(t_minishell *env, int *p_end)
{
	pid_t	pid;

	while (env->curr_cmd)
	{
		if (pipe(p_end) == -1)
			return (perror(get_shell_name()), EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
		{
			if (env->last_fd0)
				close(env->last_fd0);
			return (close(p_end[0]), close(p_end[1]), perror(get_shell_name()),
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

short	exec(t_minishell *env)
{
	int	p_end[2];
	int	status;

	find_heredoc(env, env->cmds);
	env->curr_cmd = env->cmds;
	if (main_process(env, p_end))
		return (EXIT_FAILURE);
	env->curr_cmd = env->cmds;
	while (env->curr_cmd)
	{
		waitpid(env->curr_cmd->pid, &status, 0);
		// Boucle supplementaire pour gerer les multiples heredoc dans la meme commande
		if (env->curr_cmd->infile
			&& env->curr_cmd->infile->type == TOKEN_HEREDOC)
			unlink(env->curr_cmd->infile->value);
		env->curr_cmd = env->curr_cmd->next;
	}
	env->last_err_code = WEXITSTATUS(status);
	return (close(p_end[0]), close(p_end[1]), 0);
}
