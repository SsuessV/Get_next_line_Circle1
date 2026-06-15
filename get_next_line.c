/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suyoun <suyoun@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 05:02:41 by suyoun            #+#    #+#             */
/*   Updated: 2026/06/15 13:12:44 by suyoun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_n_append(char *storage, int fd)
{
	char		*chunk;
	ssize_t 	bytes;

	chunk = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!chunk)
		return (NULL);
	while (storage == NULL || !ft_strchr(storage, '\n'))
	{
		bytes = read(fd, chunk, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(chunk);
			free(storage);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		chunk[bytes] = '\0';
		storage = ft_strjoin(storage, chunk);
	}
	free(chunk);
	return (storage);
}

//a function for extracting each line

//update storage

char *get_next_line(int fd) //call everything here