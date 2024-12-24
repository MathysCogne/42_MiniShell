/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:05:06 by mcogne--          #+#    #+#             */
/*   Updated: 2024/12/24 21:12:07 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// • Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
// • In interactive mode:
// ◦ ctrl-C displays a new prompt on a new line.
// ◦ ctrl-D exits the shell.
// ◦ ctrl-\ does nothing.
/*
** CTRL-D
** Manage in get_input.c, because CTRL-D = EOF, so input is NULL and exit shell
**
*/
/*
** CTRL-\
** Nothing
** Interactive mode: TODO
*/
void	handler_sigquit(int sig)
{
	if (1 == 2 /*IN INTERACTIVE MODE*/)
		return ;
	(void)sig;
}

/*
** CTRL-C
** Clear line and Prompt a new line 
** Interactive mode: TODO
*/
void	handler_sigint(int sig)
{
	(void)sig;
	if (1 == 2 /*IN INTERACTIVE MODE*/)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_printf("\n");
	rl_redisplay();
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handler_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}
