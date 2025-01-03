/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:51:42 by achantra          #+#    #+#             */
/*   Updated: 2025/01/03 18:32:48 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_doc(t_command *cmd)
{
	char	*buffer;
	int		fd;
	char	*file;

	ft_fprintf(2, "create doc");
	file = ft_strjoin("tmp", "000");
	if (!file)
		return (perror(SHELL_NAME), FATAL_ERROR);
	while (access(file, F_OK) == 0)
	{
		if (ft_isprint(file[5] + 1))
			file[5] += 1;
		else if (ft_isprint(file[4] + 1))
			file[4] += 1;
		else if (ft_isprint(file[3] + 1))
			file[3] += 1;
	}
	cmd->infile->value = file;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(SHELL_NAME), EXIT_FAILURE);
	buffer = readline(0);
	while (buffer && ft_strncmp(buffer, cmd->limiter, ft_strlen(buffer)))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = readline(0);
	}
	if (buffer)
		free(buffer);
	// Tester qu'on a bien le warning si fin avec CTRL+D
	else
		pr_error(EOF_HERE, cmd->limiter);
	return (close(fd), 0);
}

int	find_heredoc(t_command *cmds)
{
	t_command *current;

	current = cmds;
	while (current)
	{
		if (current->infile && current->infile->type == TOKEN_HEREDOC)
		{
			current->limiter = "END"; // A enlever une fois regle
			if (create_doc(current))
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (0);
}