/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:29 by achantra          #+#    #+#             */
/*   Updated: 2025/01/06 22:51:57 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Garder le dernier fd de type redirection_out ou redirection_out_append comme fd_out et fermer les autres.
short	find_fd_out(int *p_end, t_command *cmd)
{
	t_input	*last_input_out;
	t_input	*tmp;
	
	tmp = cmd->redir_lst;
	last_input_out = NULL;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_REDIRECTION_OUT || tmp->token->type == TOKEN_REDIRECTION_APPEND_OUT)
			last_input_out = tmp;
		tmp = tmp->next;
	}
	if (last_input_out)
	{
		close(p_end[1]);
		if (last_input_out->token->type == TOKEN_REDIRECTION_OUT)
			return (open(last_input_out->token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644));
		else
			return (open(last_input_out->token->value, O_CREAT | O_WRONLY | O_APPEND, 0644));
	}
	else if (!cmd->is_pipe)
		return (close(p_end[1]), 1);
	else
		return (p_end[1]);
}

// Garder le dernier fd de type heredoc ou redirection_in comme fd_in et fermer les autres.
short	find_fd_in(t_minishell *env, t_command *cmd)
{
	t_input	*last_input_in;
	t_input	*tmp;
	
	tmp = cmd->redir_lst;
	last_input_in = NULL;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_REDIRECTION_IN || tmp->token->type == TOKEN_HEREDOC)
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

int	exec_builtin(t_minishell *env, t_command *cmd)
{
	// char	**builtin;
	// builtin = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	if (!ft_strcmp(cmd->cmd->value, "echo"))
	{
		if (echo(cmd->str_args))
			return (gc_clean(env->gc), delete_input(env), 1);
	}
	else if (!ft_strcmp(cmd->cmd->value, "env"))
	{
		if (env_b())
			return (gc_clean(env->gc), delete_input(env), 1);
	}
	else if (!ft_strcmp(cmd->cmd->value, "exit"))
		return (gc_clean(env->gc), delete_input(env), exit(0), 0);
	else if (!ft_strcmp(cmd->cmd->value, "pwd"))
	{
		if (pwd_b())
			return (gc_clean(env->gc), delete_input(env), 1);
	}
	else if (!ft_strcmp(cmd->cmd->value, "cd"))
	{
		if (cd(cmd->str_args))
			return (gc_clean(env->gc), delete_input(env), 1);
	}
	/*
	else if (!ft_strcmp(cmd->cmd->value, "export"))
	{
		if (export(cmd->str_args))
			return (gc_clean(env->gc), delete_input(env), 1);
	}
	else if (!ft_strcmp(cmd->cmd->value, "unset"))
	{
		if (unset(env, cmd->str_args))
			return (gc_clean(env->gc), delete_input(env), 1);
	}*/
	return (gc_clean(env->gc), delete_input(env), 0);
}

int	open_redir(t_command *cmd)
{
	int	fd;
	t_input	*tmp;
	
	tmp = cmd->redir_lst;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_REDIRECTION_IN || tmp->token->type == TOKEN_HEREDOC)
			fd = open(tmp->token->value, O_RDONLY);
		else if (tmp->token->type == TOKEN_REDIRECTION_OUT)
			fd = open(tmp->token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (tmp->token->type == TOKEN_REDIRECTION_APPEND_OUT)
			fd = open(tmp->token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (perror(tmp->token->value), 1);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}

int	child_process(int *p_end, t_minishell *env, t_command *cmd)
{
	int	fd_in;
	int	fd_out;

	close(p_end[0]);
	if (open_redir(cmd))
		return (close(p_end[1]), EXIT_FAILURE);
	fd_in = find_fd_in(env, cmd);
	if (fd_in < 0)
		return (close(p_end[1]), pr_error(NO_FILE, cmd->infile->value),
			EXIT_FAILURE);
	fd_out = find_fd_out(p_end, cmd);
	if (fd_out < 0)
		return (close(p_end[1]), close(fd_in), pr_error(NO_FILE,
				cmd->outfile->value), EXIT_FAILURE);
	// ft_fprintf(2, "last_fd0 = %d\n", env->last_fd0);
	// ft_fprintf(2, "fd_in = %d\n", fd_in);
	// ft_fprintf(2, "fd_out = %d\n", fd_out);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (cmd->cmd->type == TOKEN_ARGUMENT)
		return (pr_error(NOT_FOUND_ERROR, cmd->cmd->value), gc_clean(env->gc),
			delete_input(env), EXIT_FAILURE);
	else if (cmd->cmd->type == TOKEN_BUILTIN)
		return (exec_builtin(env, cmd));
	execve(cmd->cmd_path, cmd->str_args, env->envp);
	return (perror(get_shell_name()), gc_clean(env->gc), delete_input(env),
		EXIT_FAILURE);
}
