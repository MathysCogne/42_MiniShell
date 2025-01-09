/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:16:44 by achantra          #+#    #+#             */
/*   Updated: 2025/01/09 16:03:50 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_file(int fd, char *buffer)
{
	int		nchar;
	char	*res;
	char	*temp;

	res = buffer;
	buffer = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	nchar = read(fd, buffer, BUFFER_SIZE);
	while (nchar > 0)
	{
		buffer[nchar] = 0;
		temp = res;
		res = ft_strjoin(res, buffer);
		if (!res)
			return (free(buffer), free(temp), NULL);
		free(temp);
		if (ft_strchr(res, '\n'))
			break ;
		nchar = read(fd, buffer, BUFFER_SIZE);
	}
	if (nchar < 0)
		return (free(buffer), free(res), NULL);
	return (free(buffer), res);
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*res;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i ++;
	if (buffer[i] == '\n')
		i ++;
	res = ft_substr(buffer, 0, i);
	if (!res)
		return (NULL);
	if (res[0] == 0)
		return (free(res), NULL);
	return (res);
}

void	ft_next(char *res, char **buffer)
{
	char	*temp;

	temp = *buffer;
	*buffer = ft_substr(temp, ft_strlen(res), ft_strlen(temp)
			- ft_strlen(res));
	if (!*buffer)
	{
		free(temp);
		return ;
	}
	if (*buffer[0] == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	free(temp);
}

char	*get_next_line_b(int fd)
{
	static char	*buffer;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	res = ft_line(buffer);
	if (!res)
		return (free(buffer), NULL);
	ft_next(res, &buffer);
	return (res);
}
