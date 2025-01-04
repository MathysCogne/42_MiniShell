/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:45:47 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/04 16:15:34 by achantra         ###   ########.fr       */
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
	//
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
	t_token				*limiter_herdoc;
	int					is_pipe;
	char				*cmd_path;
	char				*error_msg;
	char				**str_args;
	char				*limiter;
	pid_t				pid;
	//
	struct s_command	*next;
	struct s_command	*prev;
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