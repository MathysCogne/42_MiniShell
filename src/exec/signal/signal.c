/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:05:06 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/10 15:21:16 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Reset signal for shild process
*/
void	setup_signal_in_process(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
** CTRL-C
** Clear line and prompt a new line
** In process: Just prompt new line
*/
void	handler_sigint(int sig, siginfo_t *info, void *context)
{
	static pid_t	pid_shell = 0;

	(void)sig;
	(void)context;
	if (!pid_shell)
	{
		pid_shell = info->si_pid;
		return ;
	}
	if (info->si_pid && info->si_pid == pid_shell)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf(YELLOW BOLD "\n");
		rl_redisplay();
	}
	else
		ft_printf("\n");
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &handler_sigint;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	kill(0, SIGINT);
}
