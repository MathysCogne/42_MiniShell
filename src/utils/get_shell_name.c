/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcogne-- <mcogne--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:18:14 by mcogne--          #+#    #+#             */
/*   Updated: 2025/01/06 20:36:03 by mcogne--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_shell_name(void)
{
	char	*shell_name;

	shell_name = CYAN SHELL_NAME C_RESET;
	return (shell_name);
}
