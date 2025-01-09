/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:35:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/09 18:21:34 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Coucou
// J'ai test | echo "coucou"
// Et ca marche alors que sa devrait pas, (On est sense rien affiche)
// Tu veux que je reset mes msg d'error,
// Ou tu le protege dans l'exec si une commande et vide on s'arrete ?

int	handle_process_error(t_minishell *env, int *p_end)
{
	if (p_end)
	{
		close(p_end[0]);
		close(p_end[1]);
	}
	if (env->last_fd0)
		close(env->last_fd0);
	perror(SHELL_NAME);
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
		{
			setup_signal_in_process();
			exit(child_process(p_end, env, env->curr_cmd));
		}
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

int	simple_cmd(t_minishell *env)
{
	if (open_redir(env->cmds))
		return (EXIT_FAILURE);
	if (!ft_strcmp(env->cmds->cmd->value, "echo"))
		return (echo(env->cmds->str_args));
	else if (!ft_strcmp(env->cmds->cmd->value, "env"))
		return (env_b(env));
	else if (!ft_strcmp(env->cmds->cmd->value, "exit"))
		return (ft_putendl_fd("exit", 1), exit_b(env, env->cmds->str_args));
	else if (!ft_strcmp(env->cmds->cmd->value, "pwd"))
		return (pwd_b());
	if (!ft_strcmp(env->cmds->cmd->value, "cd"))
		return (cd(env->cmds->str_args));
	else if (!ft_strcmp(env->cmds->cmd->value, "export"))
		return (export_b(env, env->cmds->str_args));
	/*else if (!ft_strcmp(env->cmds->cmd->value, "unset"))
		return (unset_b(env, env->cmds->str_args));*/
	return (0);
}

/*
** HOLA ! Tu peux me set last error pour ces cas:
**
** 32512 -> Pas les droits exec (Correspond a 126)
** 32512 -> Cmd introuvable (Correspond a 127)
*/

short	exec(t_minishell *env)
{
	int	p_end[2];
	int	status;

	if (env->error_msg)
		return (ft_fprintf(2, "%s\n", env->error_msg), 0);
	env->last_fd0 = 0;
	find_heredoc(env->cmds);
	if (!env->cmds->is_pipe && env->cmds->cmd->type == TOKEN_BUILTIN)
	{
		env->last_err_code = simple_cmd(env);
		return (clean_heredoc(env), 0);
	}
	else
	{
		env->curr_cmd = env->cmds;
		if (main_process(env, p_end))
			return (EXIT_FAILURE);
		env->curr_cmd = env->cmds;
		while (env->curr_cmd)
		{
			waitpid(env->curr_cmd->pid, &status, 0);
			env->curr_cmd = env->curr_cmd->next;
		}
	}
	clean_heredoc(env);
	env->last_err_code = status;
	return (close(p_end[0]), close(p_end[1]), 0);
}
