/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:29 by achantra          #+#    #+#             */
/*   Updated: 2025/01/13 17:19:49 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	find_fd_out(int *p_end, t_command *cmd)
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
			return (close(p_end[1]), open(last_input_out->token->value,
					O_CREAT | O_WRONLY | O_TRUNC, 0644));
		else
			return (close(p_end[1]), open(last_input_out->token->value,
					O_CREAT | O_WRONLY | O_APPEND, 0644));
	}
	else if (!cmd->is_pipe)
		return (close(p_end[1]), 1);
	else
		return (p_end[1]);
}

short	find_fd_in(t_minishell *env, t_command *cmd)
{
	t_input	*last_input_in;
	t_input	*tmp;

	tmp = cmd->redir_lst;
	last_input_in = NULL;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_REDIRECTION_IN
			|| tmp->token->type == TOKEN_HEREDOC)
			last_input_in = tmp;
		tmp = tmp->next;
	}
	if (last_input_in)
	{
		close(env->last_fd0);
		return (open(last_input_in->token->value, O_RDONLY));
	}
	return (env->last_fd0);
}

int	dup_fd(int fd_in, int fd_out)
{
	int	err;

	if (fd_in != 0)
	{
		err = dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		if (err)
			return (close(fd_out), err);
	}
	if (fd_out != 1)
	{
		err = dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		if (err)
			return (err);
	}
	return (0);
}

int	path_error(t_minishell *env, char *cmd_path)
{
	if (access(cmd_path, F_OK) != 0)
		return (pr_error(NO_FILE, cmd_path), clean_child(env), 1);
	else if (access(cmd_path, X_OK) != 0)
		return (pr_error(PERM_ERROR, cmd_path), clean_child(env), 126);
	return (0);
}

int	child_process(int *p_end, t_minishell *env, t_command *cmd)
{
	int	fd_in;
	int	fd_out;

	close(p_end[0]);
	if (open_redir(cmd))
		return (close(p_end[1]), clean_child(env), EXIT_FAILURE);
	fd_in = find_fd_in(env, cmd);
	if (fd_in < 0)
		return (close(p_end[1]), perror(SHELL_NAME), clean_child(env), 1);
	fd_out = find_fd_out(p_end, cmd);
	if (fd_out < 0)
		return (close(p_end[1]), close(fd_in), perror(SHELL_NAME),
			clean_child(env), EXIT_FAILURE);
	if (dup_fd(fd_in, fd_out) < 0)
		return (perror(SHELL_NAME), clean_child(env), EXIT_FAILURE);
	if (!cmd->cmd)
		return (clean_child(env), 0);
	if (cmd->cmd->type == TOKEN_ARGUMENT)
		return (pr_error(NF_ERROR, cmd->cmd->value), clean_child(env), 127);
	else if (cmd->cmd->type == TOKEN_BUILTIN)
		return (exec_builtin(env, cmd, fd_out));
	if (access(cmd->cmd_path, F_OK) != 0 || access(cmd->cmd_path, X_OK) != 0)
		return (path_error(env, cmd->cmd_path));
	execve(cmd->cmd_path, cmd->str_args, env->envp);
	return (perror(SHELL_NAME), clean_child(env), 1);
}
