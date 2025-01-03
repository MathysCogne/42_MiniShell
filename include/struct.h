/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:45:47 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/03 00:31:12 by mcogne--         ###   ########.fr       */
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
	t_token				*command;
	t_token				**args;
	t_token				*out_file;
	t_token				*in_file;
	int					is_pipe;
	char				*error_msg;
	char				*cmd_and_args;
	// CHAR PATH_COMMAND;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_minishell
{
	t_input				*input;
	t_command			*commands;
	t_gc				*gc;
	// char				*last_err_code;
}						t_minishell;

#endif