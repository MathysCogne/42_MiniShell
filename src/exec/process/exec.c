/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:35:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/12 22:23:59 by achantra         ###   ########.fr       */
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
	perror(SHELL_NAME);
	return (EXIT_FAILURE);
}

int	open_redir(t_command *cmd)
{
	int		fd;
	t_input	*tmp;

	tmp = cmd->redir_lst;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_REDIRECTION_IN
			|| tmp->token->type == TOKEN_HEREDOC)
			fd = open(tmp->token->value, O_RDONLY);
		else if (tmp->token->type == TOKEN_REDIRECTION_OUT)
			fd = open(tmp->token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (tmp->token->type == TOKEN_REDIRECTION_APPEND_OUT)
			fd = open(tmp->token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (ft_putstr_fd(SHELL_NAME, 2), ft_putstr_fd(": ", 2),
				perror(tmp->token->value), 1);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
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
	env->is_child = 0;
	if (open_redir(env->cmds))
		return (EXIT_FAILURE);
	else if (!ft_strcmp(env->cmds->cmd->value, "env"))
		return (env_b(env));
	else if (!ft_strcmp(env->cmds->cmd->value, "exit"))
		return (ft_putendl_fd("exit", 1), exit_b(env, env->cmds->str_args));
	if (!ft_strcmp(env->cmds->cmd->value, "cd"))
		return (cd(env->cmds->str_args));
	else if (!ft_strcmp(env->cmds->cmd->value, "export"))
		return (export_b(env, env->cmds->str_args));
	else if (!ft_strcmp(env->cmds->cmd->value, "unset"))
		return (unset_b(env, env->cmds->str_args));
	return (0);
}

short	exec(t_minishell *env)
{
	int	p_end[2];

	if (env->error_msg)
		return (ft_putendl_fd(env->error_msg, 2), 0);
	env->last_fd0 = 0;
	find_heredoc(env->cmds);
	if (env->cmds && !env->cmds->is_pipe && env->cmds->cmd
		&& env->cmds->cmd->type == TOKEN_BUILTIN
		&& ft_strcmp(env->cmds->cmd->value, "echo")
		&& ft_strcmp(env->cmds->cmd->value, "pwd"))
		return (env->last_err_code = simple_cmd(env), clean_heredoc(env), 0);
	else
	{
		env->curr_cmd = env->cmds;
		if (main_process(env, p_end))
			return (EXIT_FAILURE);
		env->curr_cmd = env->cmds;
		while (env->curr_cmd)
		{
			waitpid(env->curr_cmd->pid, &env->last_err_code, 0);
			env->curr_cmd = env->curr_cmd->next;
		}
		env->is_child = 1;
	}
	return (clean_heredoc(env), close(p_end[0]), close(p_end[1]), 0);
}
