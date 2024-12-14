/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:52:28 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/14 22:44:29 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "libft_extra.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

/*******************************/
/*            MACROS           */
/*******************************/

# define TOKEN_SEPARATOR " \t\r"
# define SHELL_NAME "bzh » "

/*******************************/
/*          STRUCTURE          */
/*******************************/
typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_REDIRECTION_APPEND,
	TOKEN_PIPE
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_input
{
	t_token			*token;
	size_t			pos;
	struct s_input	*next;
	struct s_input	*prev;
}					t_input;

typedef struct s_minishell
{
	t_input			*input;
	t_gc			*gc;
}					t_minishell;

/*******************************/
/*           PARSING           */
/*******************************/
short				parsing(t_minishell *env);
short				ft_get_input(t_minishell *env);
short				init_struct_env(t_minishell *env);
void				debug_print_input(t_input *input);
void				ft_clean_input(t_minishell *env);
short				add_token(t_minishell *env, char *value, t_token_type type,
						size_t pos);

/*******************************/
/*            EXEC             */
/*******************************/

/*******************************/
/*            UTILS            */
/*******************************/
char				**ft_split_sep(char const *s, char *sep);

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