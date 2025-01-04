/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:51:42 by achantra          #+#    #+#             */
/*   Updated: 2025/01/04 20:51:59 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*put_token(t_minishell *env, char *value, t_token_type type)
{
	t_token	*new_token;
	t_input	*new_input;

	new_token = create_token(env, value, type);
	if (!new_token)
		return (NULL);
	new_input = create_input(env, new_token);
	if (!new_input)
		return (NULL);
	input_add_back(&env->input, new_input);
	return (new_token);
}

int	create_doc(t_minishell *env, t_command *cmd)
{
	char	*buffer;
	int		fd;
	char	*file;

	// Remplacer par une gestion aleatoire de nom de fichier.
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
	cmd->infile = put_token(env, file, TOKEN_HEREDOC);
	if (!cmd->infile)
		return (2);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(SHELL_NAME), EXIT_FAILURE);
	buffer = get_next_line(0);
	while (buffer && ft_strncmp(buffer, cmd->limiter_hd->value, ft_strlen(buffer) - 1))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(0);
	}
	if (buffer)
		free(buffer);
	else
		pr_error(EOF_HERE, cmd->limiter_hd->value);
	return (close(fd), 0);
}

int	find_heredoc(t_minishell *env, t_command *cmds)
{
	t_command *current;

	current = cmds;
	while (current)
	{
/*
Modif : pour chaque commande, prendre la liste des redirections
A chaque heredoc, lancer le remplissage du heredoc
*/ 
		if (current->limiter_hd && current->limiter_hd->type == TOKEN_HEREDOC)
		{
			if (create_doc(env, current))
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (0);
}

/*
Pour chaque commande, prendre la liste des redirections
A chaque heredoc, lancer le remplissage du heredoc
*/ 