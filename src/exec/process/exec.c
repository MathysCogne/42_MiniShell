/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:35:07 by achantra          #+#    #+#             */
/*   Updated: 2025/01/13 18:11:25 by achantra         ###   ########.fr       */
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

void	simple_cmd(t_minishell *env)
{
	int	fd_out;

	env->is_child = 0;
	fd_out = check_redir(env->cmds);
	if (fd_out < 0)
		return (env->last_err_code = EXIT_FAILURE, clean_child(env));
	else if (!ft_strcmp(env->cmds->cmd->value, "env"))
		env->last_err_code = env_b(env);
	else if (!ft_strcmp(env->cmds->cmd->value, "exit"))
	{
		ft_putendl_fd("exit", 1);
		env->last_err_code = exit_b(env, env->cmds->str_args);
	}
	if (!ft_strcmp(env->cmds->cmd->value, "cd"))
		env->last_err_code = cd(env->cmds->str_args);
	else if (!ft_strcmp(env->cmds->cmd->value, "export"))
		env->last_err_code = export_b(env, env->cmds->str_args);
	else if (!ft_strcmp(env->cmds->cmd->value, "unset"))
		env->last_err_code = unset_b(env, env->cmds->str_args);
	else if (!ft_strcmp(env->cmds->cmd->value, "echo"))
		env->last_err_code = echo(env->cmds->str_args, fd_out);
	else if (!ft_strcmp(env->cmds->cmd->value, "pwd"))
		env->last_err_code = pwd_b(fd_out);
	if (fd_out > 2)
		close(fd_out);
}

short	exec(t_minishell *env)
{
	int	p_end[2];
	int	status;

	if (env->error_msg)
		return (ft_putendl_fd(env->error_msg, 2), 0);
	env->last_fd0 = 0;
	find_heredoc(env->cmds);
	if (env->cmds && !env->cmds->is_pipe && env->cmds->cmd
		&& env->cmds->cmd->type == TOKEN_BUILTIN)
		return (simple_cmd(env), clean_heredoc(env), 0);
	else
	{
		env->is_child = 1;
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
	env->last_err_code = status;
	return (clean_heredoc(env), close(p_end[0]), close(p_end[1]), 0);
}
