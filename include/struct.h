/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:45:47 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/03 15:21:33 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft_extra.h"

typedef enum e_token_type
{
	TOKEN_BUILTIN,
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_HEREDOC,
	TOKEN_REDIRECTION_APPEND_OUT,
	TOKEN_PIPE
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
}						t_token;

typedef struct s_input
{
	t_token				*token;
	struct s_input		*next;
	struct s_input		*prev;
}						t_input;

typedef struct s_command
{
	t_token				*cmd;
	t_token				**args;
	t_token				*outfile;
	t_token				*infile;
	int					is_pipe;
	char				*error_msg;
	char				*exec_args;
	// En attendant le correctif
	char				**exec_args2;
	// CHAR *PATH_COMMAND;
	char				*cmd_path;
	// CHAR *LIMITER;
	char				*limiter;
	struct s_command	*next;
	struct s_command	*prev;
	pid_t				pid;
}						t_command;

typedef struct s_minishell
{
	t_input				*input;
	t_command			*cmds;
	t_command			*curr_cmd;
	t_gc				*gc;
	char				**envp;
	int					last_err_code;
	int					last_fd0;
}						t_minishell;

#endif