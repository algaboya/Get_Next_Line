/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:59:07 by algaboya          #+#    #+#             */
/*   Updated: 2024/04/11 22:16:21 by algaboya         ###   ########.fr       */
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
		// if (temp_buffer == NULL)
		// 	break ;
		temp_buffer[read_chars] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
		// printf("#####\n");
		// printf("%s\n", buffer);
		// printf("%s\n", temp_buffer);
		// printf("%d\n", ft_strchr(buffer));
		// printf("%d\n", read_chars);
	}
	free(temp_buffer);
	// temp_buffer = NULL;
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
	i++;
	// printf("%d\n",i);
	clean = (char *)malloc(sizeof(char) * (i + 1));
	if (!clean)
		return (NULL);
	return(NULL);
	ft_strlcpy(clean, buffer, i + 1);
	// if (!clean)
	// 	return (buffer);
	// printf("#####\n");
	// printf("%s\n", buffer);
	// printf("%s\n", clean);

	return (clean);
}

char	*ft_final(char *buffer, char *line)
{
	char	*next;
	int		i;
	int		j;

	// if (!buffer)
	// 	return (NULL);
	i = ft_strlen(buffer); 
	j = ft_strlen(line);
	// if (j == 0)
	// 	return (buffer);
	// else
	// {
		next = (char *)malloc(sizeof(char) * (i - j + 1));
		if (!next)
			return (NULL);
		ft_strlcpy(next, buffer + j, (i - j + 1));
		free(buffer);
		// printf("#####\n");
		// printf("%s\n", buffer);
	// }
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
	buffer = ft_read(buffer, fd);
	if (!buffer)
		return (free(buffer), NULL);
	line = ft_clean(buffer);
	// buffer = ft_final(buffer, line);
	return (line);
}

 int	main()
 {
 	int		fd;

 	fd = open("example.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	while (1)
	{
		/* code */
	}
   	close(fd);
 	return (0);
 }