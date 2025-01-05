/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:29 by achantra          #+#    #+#             */
/*   Updated: 2025/01/04 23:21:19 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	find_fd_out(int *p_end, t_command *cmd)
{
	// Garder le dernier fd de type redirection_out ou redirection_out_append comme fd_out et fermer les autres.
	if (cmd->outfile && cmd->outfile->type == TOKEN_REDIRECTION_OUT)
	{
		close(p_end[1]);
		return (open(cmd->outfile->value, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	}
	else if (cmd->outfile && cmd->outfile->type == TOKEN_REDIRECTION_APPEND_OUT)
	{
		close(p_end[1]);
		return (open(cmd->outfile->value, O_CREAT | O_WRONLY | O_APPEND, 0644));
	}
	else if (!cmd->is_pipe)
	{
		close(p_end[1]);
		return (1);
	}
	else
		return (p_end[1]);
}

short	find_fd_in(t_minishell *env, t_command *cmd)
{
	// Garder le dernier fd de type heredoc ou redirection_in comme fd_in et fermer les autres.
	if (cmd->infile && (cmd->infile->type == TOKEN_REDIRECTION_IN
			|| cmd->infile->type == TOKEN_HEREDOC))
	{
		close(env->last_fd0);
		return (open(cmd->infile->value, O_RDONLY));
	}
	return (env->last_fd0);
}

int	exec_builtin(t_minishell *env, t_command *cmd)
{
	char	**builtin;
	int		i;

	builtin = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit",
		NULL};
	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(cmd->cmd->value, builtin[i]))
			break ;
		i++;
	}
	if (echo(cmd->str_args))
		return (gc_clean(env->gc), delete_input(env), 1);
	return (gc_clean(env->gc), delete_input(env), 0);
}

int	child_process(int *p_end, t_minishell *env, t_command *cmd)
{
	int	fd_in;
	int	fd_out;

	close(p_end[0]);
	// Parcourir toutes les redirections.
	// Ouvrir tous les fichiers avec les bonnes options selon input ou output.
	// S arreter si impossible d en ouvrir un, tout refermer et clean et fin d exec.
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
