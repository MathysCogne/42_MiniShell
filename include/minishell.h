/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:28 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/25 15:44:51 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_SOURCE 1
# define _POSIX_C_SOURCE 200809L

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "libft_extra.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>

/*******************************/
/*            MACROS           */
/*******************************/

// SPACE(3)
# define TOKEN_SEPARATOR " \t\n\v\f\r"
# define SHELL_NAME "bzh » "

/*******************************/
/*          STRUCTURE          */
/*******************************/

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
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_minishell
{
	t_input				*input;
	t_command			*commands;
	t_gc				*gc;
}						t_minishell;

/*******************************/
/*           PARSING           */
/*******************************/
short					parsing(t_minishell *env);
short					get_input(t_minishell *env);
void					delete_input(t_minishell *env);
short					put_input(t_minishell *env, char *value,
							t_token_type type);
t_token_type			tokenization(char *token);
//
short					analys_semantic(t_minishell *env);
t_command				*create_command(t_token *token);
// Utils Parsing
short					init_struct_env(t_minishell *env);
void					debug_print_input(t_input *input);
void					debug_print_commands(t_command *commands);
short					is_external_command(char *token);
short					is_internal_command(char *token);

/*******************************/
/*            EXEC             */
/*******************************/
void					setup_signal(void);
/*******************************/
/*            UTILS            */
/*******************************/
char					**ft_split_minishell(char const *s, char *sep);
void					free_split(char **tab);
short					is_sep(char c, char *sep);
size_t					handle_quotes(const char *str, size_t i);

/*******************************/
/*            COLORS           */
/*******************************/
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define BOLD "\033[1m"
# define ITALIC "\033[3m"
# define UDERLINE "\033[4m"
# define C_RESET "\033[0m"

#endif