/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suyoun <suyoun@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 05:02:41 by suyoun            #+#    #+#             */
/*   Updated: 2026/08/03 15:31:49 by suyoun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_n_append(char *storage, int fd)
{
	char		*temp_buf;
	ssize_t		bytes;

	temp_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buf)
		return (NULL);
	while (42)
	{
		bytes = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free(temp_buf), free(storage), NULL);
		if (bytes == 0)
			break ;
		temp_buf[bytes] = '\0';
		storage = join_and_free(storage, temp_buf);
		if (!storage)
			return (free(temp_buf), NULL);
		if (ft_strchr(temp_buf, '\n'))
			break ;
	}
	free(temp_buf);
	if (storage && storage[0] == '\0')
		return (free(storage), NULL);
	return (storage);
}

char	*join_and_free(char *storage, char *temp_buf)
{
	char	*new_storage;

	new_storage = ft_strjoin(storage, temp_buf);
	free(storage);
	return (new_storage);
}

char	*extract_line(char *storage)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!storage)
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	new_line = malloc((i + 2) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (storage[i] != '\n' && storage[i] != '\0')
	{
		new_line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		new_line[i] = '\n';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*update_storage(char *storage)
{
	int		i;
	int		j;
	char	*leftover_storage;

	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	if (storage[i] == '\0')
		return (free(storage), NULL);
	i++;
	j = 0;
	while (storage[i + j] != '\0')
		j++;
	leftover_storage = malloc ((j + 1) * sizeof(char));
	if (!leftover_storage)
		return (free(storage), NULL);
	j = 0;
	while (storage [i + j] != '\0')
	{
		leftover_storage[j] = storage[i + j];
		j++;
	}
	leftover_storage[j] = '\0';
	free(storage);
	return (leftover_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_n_append(storage, fd);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = update_storage(storage);
	return (line);
}
/*
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	i = 1;
	// line = get_next_line(fd);
	// if (line)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// }
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("CALL %d:\n", i);
		printf("%s", line);
		printf("----------------\n");
		free(line);
		i++;
	}

	close(fd);
	return (0);
}
*/
