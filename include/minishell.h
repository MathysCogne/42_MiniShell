/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:28 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/13 18:10:57 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_SOURCE 1
# define _POSIX_C_SOURCE 200809L
// # define _GNU_SOURCE

# include "ft_printf.h"
# include "libft.h"
# include "libft_extra.h"
# include "struct.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*******************************/
/*            DEFINE           */
/*******************************/

# define TOKEN_SEPARATOR " \t\n\v\f\r"
# define SHELL_NAME "bzh"
# define ERR_SYNTAX "bzh: syntax error near unexpected token "

/*******************************/
/*         TOKENISATION        */
/*******************************/
short			parsing(t_minishell *env);

short			get_input(t_minishell *env);
short			put_input(t_minishell *env, char *value, t_token_type type);
void			input_add_back(t_input **input, t_input *new);
t_token			*create_token(char *value, t_token_type type);
t_input			*create_input(t_token *token);
t_token_type	tokenization(t_minishell *env, char *token);

/*******************************/
/*       ANALYSE SEMANTIC      */
/*******************************/
short			analyse_semantic(t_minishell *env);
short			handler_redirection(t_input *input, t_command *command);
short			extract_args(t_command *command);
short			add_arg_command(t_token *token, t_command *command);
void			add_back_command(t_command **commands, t_command *new_command);
t_command		*create_command(void);
short			find_path_and_cmd(t_minishell *env, t_command *command);
short			handler_validate_command(t_minishell *env, t_input *input,
					t_command *command);

/*******************************/
/*         QUOTE EXPAND        */
/*******************************/
short			handler_quote_expand(t_minishell *env, t_input *input);
char			*expand_var(t_minishell *env, t_token *token);
short			handler_quote(t_token *token);
short			delete_anti_slash(t_token *token);
short			check_single_quotes(char *str);
char			*expand_last_err_code(t_minishell *env, char *var);

/*******************************/
/*         UTILS PARSING       */
/*******************************/
void			debug_print_input(t_input *input);
void			debug_print_commands(t_command *commands);
void			free_input(t_input *input);
void			delete_input(t_minishell *env);
short			init_struct_env(t_minishell *env);
void			free_split(char **tab);

/*******************************/
/*             EXEC            */
/*******************************/
# define FATAL_ERROR 2
# define PERM_ERROR_END 10
# define PERM_ERROR 11
# define NF_ERROR 12
# define NO_PATH 13
# define NO_FILE 14
# define EOF_HERE 15
# define EXIT_NF 127
# define BUFFER_SIZE 1000

// Exec process
void			clean_environ(t_minishell *env);
void			clean_child(t_minishell *env);
void			clean_heredoc(t_minishell *env);
short			f_fd_out(t_command *cmd);
int				check_redir(t_command *cmds);
int				open_redir(t_command *cmd);
char			*get_next_line_b(int fd);
int				find_heredoc(t_command *cmds);
short			exec(t_minishell *env);
void			pr_error(int e, char *element);
int				child_process(int *p_end, t_minishell *env, t_command *cmd);
// Signal
void			setup_signal(void);
void			setup_signal_in_process(void);
// Builtins
int				alloc_env(t_minishell *env);
void			export_error(char *arg);
int				export_b(t_minishell *env, char **args);
int				exit_b(t_minishell *env, char **arg);
int				echo(char **args, int fd_out);
int				env_b(t_minishell *env);
int				pwd_b(int fd_out);
int				cd(char **args);
int				unset_b(t_minishell *env, char **arg);
int				exec_builtin(t_minishell *env, t_command *cmd, int fd_out);

/*******************************/
/*            UTILS            */
/*******************************/
// SPLIT MINISHELL
char			**ft_split_minishell(const char *s, char *sep);
short			is_sep(char c, char *sep);
char			**free_error_alloc(size_t i, char **tab);
size_t			skip_word(const char *str, size_t i, char *sep);
size_t			get_word_len(const char *str, char *sep);
short			is_redir(char const *s, size_t i);
size_t			skip_redir(const char *str, size_t i);
size_t			get_redir_len(const char *str);
short			is_quote(char const *str, size_t i);
size_t			handle_quotes(const char *str, size_t i);
// UTILS
size_t			ft_tablen(void **tab);
char			*get_shell_name(void);
char			*is_external_command(t_minishell *env, char *token);
short			is_builtin_command(char *token);

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

# define TURQUOISE_BLUE "\033[38;2;0;184;169m"
# define DARK_GRAY "\033[38;2;47;52;59m"
# define PALE_PINK "\033[38;2;245;166;195m"
# define MINT_GREEN "\033[38;2;136;199;153m"

#endif