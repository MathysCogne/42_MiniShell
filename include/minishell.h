/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/01 23:53:13 by mcogne--         ###   ########.fr       */
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
# include "struct.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>

/*******************************/
/*            MACROS           */
/*******************************/

# define TOKEN_SEPARATOR " \t\n\v\f\r"
# define QUOTE_SINGLE '\''
# define QUOTE_DOUBLE '"'

# define SHELL_NAME "bzh » "
# define ERR_SYNTAX "Syntax error: "

/*******************************/
/*           PARSING           */
/*******************************/
short			parsing(t_minishell *env);
// Tokenization
short			get_input(t_minishell *env);
void			delete_input(t_minishell *env);
short			put_input(t_minishell *env, char *value, t_token_type type);
t_token_type	tokenization(char *token);
// Analys Semantic
short			analys_semantic(t_minishell *env);
t_command		*create_command(t_token *token);
void			add_back_command(t_command **commands, t_command *new_command);
short			add_arg_command(t_token *token, t_command *command);
short			handler_validate_command(t_input *input, t_command *command);
short			handler_redirection(t_input *input, t_command *command);
short			handler_pipe(t_input *input, t_command *command);
short			handler_argument(t_input *input, t_command *command);
short			handler_quote_expand(t_token *token, t_command *command);
// Utils Parsing
short			init_struct_env(t_minishell *env);
void			debug_print_input(t_input *input);
void			debug_print_commands(t_command *commands);
short			is_external_command(char *token);
short			is_internal_command(char *token);

/*******************************/
/*            EXEC             */
/*******************************/
short			exec(t_minishell *env);
//
void			setup_signal(void);

/*******************************/
/*            UTILS            */
/*******************************/
char			**ft_split_minishell(char const *s, char *sep);
void			free_split(char **tab);
short			is_sep(char c, char *sep);
size_t			handle_quotes(const char *str, size_t i);

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