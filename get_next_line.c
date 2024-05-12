/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:59:07 by algaboya          #+#    #+#             */
/*   Updated: 2024/04/14 21:59:17 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(char *buffer, int fd)
{
	int		read_chars;
	char	*temp_buffer;

	temp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (temp_buffer == NULL)
		return (NULL);
	read_chars = 1;
	while (read_chars != 0 && !ft_strchr(buffer))
	{
		read_chars = read(fd, temp_buffer, BUFFER_SIZE);
		if (read_chars == -1)
			return (free (temp_buffer), NULL);
		temp_buffer[read_chars] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
	}
	free(temp_buffer);
	return (buffer);
}

char	*ft_clean(char *buffer)
{
	char	*clean;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	clean = (char *)malloc(sizeof(char) * (i + 1));
	if (!clean)
		return (NULL);
	ft_strlcpy(clean, buffer, i + 1);
	return (clean);
}

char	*ft_final(char *buffer)
{
	char	*next;
	int		i;
	int		len;

	if (!buffer)
		return (NULL);
	i = 0;
	len = ft_strlen(buffer);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!next)
		return (free(buffer), NULL);
	ft_strlcpy(next, buffer + i, (len - i + 1));
	free(buffer);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
	buffer = ft_read(buffer, fd);
	line = ft_clean(buffer);
	buffer = ft_final(buffer);
	return (line);
}
