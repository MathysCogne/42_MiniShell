/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:51:42 by achantra          #+#    #+#             */
/*   Updated: 2025/01/10 11:36:52 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_file_name(void)
{
	char	*file;

	file = ft_strjoin("tmp", "0000");
	if (!file)
		return (NULL);
	while (access(file, F_OK) == 0)
	{
		if (ft_isprint(file[6] + 1))
			file[6] += 1;
		if (ft_isprint(file[5] + 1))
			file[5] += 1;
		else if (ft_isprint(file[4] + 1))
			file[4] += 1;
		else if (ft_isprint(file[3] + 1))
			file[3] += 1;
	}
	return (file);
}

int	create_doc(t_token *hd)
{
	char	*buffer;
	int		fd;
	char	*file;

	file = find_file_name();
	if (!file)
		return (perror(SHELL_NAME), FATAL_ERROR);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(SHELL_NAME), EXIT_FAILURE);
	ft_putstr_fd("> ", 1);
	buffer = get_next_line_b(0);
	while (buffer && ft_strncmp(buffer, hd->value, ft_strlen(buffer) - 1))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		ft_putstr_fd("> ", 1);
		buffer = get_next_line_b(0);
	}
	if (!buffer)
		pr_error(EOF_HERE, hd->value);
	else
		free(buffer);
	hd->value = file;
	return (close(fd), 0);
}

int	find_heredoc(t_command *cmds)
{
	t_command	*current;
	t_input		*tmp;

	current = cmds;
	while (current)
	{
		tmp = current->redir_lst;
		while (tmp)
		{
			if (tmp->token->type == TOKEN_HEREDOC)
			{
				if (create_doc(tmp->token))
					return (EXIT_FAILURE);
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
	return (0);
}
