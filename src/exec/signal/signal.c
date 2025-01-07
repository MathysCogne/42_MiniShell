/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:05:06 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/07 22:17:05 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** CTRL-C
** Clear line and Prompt a new line
** Interactive mode: Just prompt new line
*/
void	handler_sigint(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (info->si_pid == getpid())
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf("\n");
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
}
